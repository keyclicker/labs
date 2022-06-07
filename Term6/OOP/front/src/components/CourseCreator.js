import Card from 'react-bootstrap/Card';
import Button from 'react-bootstrap/Button';
import Form from 'react-bootstrap/Form';
import { client } from '../api/api';
import { useState } from 'react';

export function CourseCreator({state}) {
  const [name, setName] = useState("");
  const [description, setDescription] = useState("");

  const createCourse = () => {
    client.post('/course', {
      name,
      description
    });

    state.setCourses([{
      professor: state?.user,
      name,
      description,
    }, ...state.courses]);
    state.setShowCreator(false);
    setName("");
    setDescription("");
  }

  const cancelCreation = () => {
    state.setShowCreator(false);
    setName("");
    setDescription("");
  }

  return (
   <Card className="mb-3">
      <Card.Header as="h5">Create course</Card.Header>
      <Card.Body>
        <Form>
          <Form.Group className="mb-3" controlId="exampleForm.ControlInput1">
            <Form.Label>Course name</Form.Label>
            <Form.Control
              onChange={e => setName(e.target.value)}
              value={name}
              type="text"
              placeholder="Course name"
              autoFocus/>
          </Form.Group>
          <Form.Group
            className="mb-3"
            controlId="exampleForm.ControlTextarea1">
            <Form.Label>Course description</Form.Label>
            <Form.Control 
              onChange={e => setDescription(e.target.value)}
              value={description}
            as="textarea" rows={3} />
          </Form.Group>
        </Form>
      </Card.Body>
      <Card.Footer style={{display: "flex", flexDirection: "row", justifyContent: "end"}}>
          <Button variant="secondary" onClick={cancelCreation}>Cancel</Button>
          <Button variant="primary" className='ms-2' onClick={createCourse}>Create</Button>
        </Card.Footer>
    </Card>
  )
}