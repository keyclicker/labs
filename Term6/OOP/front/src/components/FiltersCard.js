import InputGroup from 'react-bootstrap/InputGroup';
import FormControl from 'react-bootstrap/FormControl';
import Button from 'react-bootstrap/Button';
import Card from 'react-bootstrap/Card';
import Form from 'react-bootstrap/Form';

export default
function FiltersCard({state}) {


  return (
    <Card className="position-fixed-lg mb-3">
      <Card.Header>Filters</Card.Header>
      <Card.Body>
        <InputGroup className="mb-3">
          <FormControl
            placeholder="Search"
            aria-label="Search"
            aria-describedby="Search"
            value={state.query}
            onChange={e => state.handleQueryChange(e.target.value)}
          />
          <Button variant="outline-secondary" id="button-addon2">
            <i class="bi bi-search"></i>
          </Button>
        </InputGroup>

        <Form.Select aria-label="Default select example">
          <option value="1">All courses</option>
          <option value="2">Enrolled</option>
        </Form.Select>
      </Card.Body>
    </Card>
  )
}