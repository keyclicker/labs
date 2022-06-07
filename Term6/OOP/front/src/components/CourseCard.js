import Col from 'react-bootstrap/Col';
import Row from 'react-bootstrap/Row';
import Button from 'react-bootstrap/Button';
import Card from 'react-bootstrap/Card';
import Accordion from 'react-bootstrap/Accordion';
import Badge from 'react-bootstrap/Badge';
import ListGroup from 'react-bootstrap/ListGroup';
import InputGroup from 'react-bootstrap/InputGroup';
import FormControl from 'react-bootstrap/FormControl';
import Image from 'react-bootstrap/Image';
import { useState } from 'react';
import { client } from '../api/api';

export default
function CourseCard({state, course}) {
  const [enrolled, setEnrolled] = useState( state.user &&
    course?.students?.some(s=>s.username == state.user.username));

  const deleteCourse = () => {
    client.delete("/course", {id: course.id});
    state.setCourses(state.courses.filter(c => c.id !== course.id));
  };

  const enroll = () => {
    client.post("/enroll", {id: course.id});
    setEnrolled(true);
  };

  const unenroll = () => {
    client.delete("/enroll", {id: course.id});
    setEnrolled(false);
  };


  return (
    <Card className="mb-3">
      <Card.Header as="h5">
        <Row className="align-items-center justify-content-between me-0 ms-0">
          {course.professor.name} - @{course.professor.username}

          {state?.user?.type == 1 &&
            (!enrolled ? <Button variant="primary" style={{width: 100}} onClick={enroll}>Enroll</Button>
            : <Button variant="danger" style={{width: 100}} onClick={unenroll}>Unenroll</Button>)}

          {state?.user?.type == 0 && state?.user?.username == 
          course.professor.username && course?.id &&
                    <Button variant="danger" style={{width: 100}} 
                    onClick={deleteCourse}>Delete</Button> }

        </Row>
      </Card.Header>
      <Card.Body>
        <Card.Title>{course.name}</Card.Title>
        <Card.Text>
          {course.description}
        </Card.Text>
        
      </Card.Body>

      <Accordion defaultActiveKey="-1">
        <Accordion.Item eventKey="0">
          <Accordion.Header>
            <span>Enrolled Students <Badge>{course?.students?.length}</Badge></span>
          </Accordion.Header>
          <Accordion.Body className="p-0">
            <StudentsList state={state} course={course}/>
          </Accordion.Body>
        </Accordion.Item>
      </Accordion>
    </Card>
  );
}

function StudentsList({state, course}) {
  return (
    <ListGroup>
      {course?.students?.map((student, index) => (
        <Student state={state} course={course} student={student} key={index}/>
      ))}
    </ListGroup>
  )
}

function Student({state, course, student}) {
  const [mark, setMark] = useState(student.mark == -1 ? 0 : student.mark);

  const rate = () =>{
    client.put("/rate", {
      course_id: course.id,
      student_username: student.username,
      mark
    });
  }

  const disabled = mark < 0 || mark > 100;
  return (
    <ListGroup.Item>
      <div className="d-flex align-items-center justify-content-between">
        <div className="d-flex align-items-center">
          <Image src="https://via.placeholder.com/50" roundedCircle />
          <span className="ms-3">{student.name}</span>
          <span className="ms-2 text-muted">@{student.username}</span>
          { student?.mark != -1 &&
            <span className="ms-2 text-muted">  {student.mark}/100</span>}
        </div>
        <div className="d-flex align-items-center">
          {state?.user?.type == 0 && state?.user?.username == course.professor.username &&
            <InputGroup>
              <FormControl
                placeholder="Mark"
                aria-label="Mark"
                value={mark}
                onChange={e => setMark(isNaN(parseInt(e.target.value)) 
                  ? 0 : parseInt(e.target.value))}
                aria-describedby="basic-addon2"/>
              <Button variant="outline-success" id="button-addon2" 
              disabled={disabled} onClick={rate}>
                Rate
              </Button>
            </InputGroup>}
        </div>
      </div>
    </ListGroup.Item>
  );
}