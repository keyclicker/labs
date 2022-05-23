import Col from 'react-bootstrap/Col';
import Row from 'react-bootstrap/Row';
import Button from 'react-bootstrap/Button';
import Card from 'react-bootstrap/Card';
import Accordion from 'react-bootstrap/Accordion';
import Badge from 'react-bootstrap/Badge';
import ListGroup from 'react-bootstrap/ListGroup';
import Image from 'react-bootstrap/Image'

export default
function CourseCard(props) {
  return (
    <Card className="mb-3">
      <Card.Header as="h5">
        <Row className="align-items-center justify-content-between me-0 ms-0">
          Шкільняк Оксана Степанівна
          <Button variant="primary" style={{width: 100}}>Enroll</Button>  
        </Row>
      </Card.Header>
      <Card.Body>
        <Card.Title>Алгоритми та складність</Card.Title>
        <Card.Text>
          Мета дисципліни - вивчення основних структур даних і алгоритмів, що використовуються
          в програмуванні та аналіз їх ефективності
        </Card.Text>
        
      </Card.Body>

      <Accordion defaultActiveKey="-1">
        <Accordion.Item eventKey="0">
          <Accordion.Header>
            <span>Enrolled Students <Badge>50</Badge></span>
          </Accordion.Header>
          <Accordion.Body className="p-0">
            <StudentsList/>
          </Accordion.Body>
        </Accordion.Item>
      </Accordion>
    </Card>
  );
}

function StudentsList() {
  let students = [
    { name: "Михайло Тірон", username: "mexalik1488" },
    { name: "Остап Микитюк", username: "ostapmk" },
    { name: "Чиківчук Микола", username: "keyclicker" },
    { name: "Олександр Короленко", username: "oleksandr_korolenko" },
    { name: "Андрій Трохимір", username: "troymer" },
    { name: "Валерій Кузьменко", username: "valeriy_kuzmenko" },
    { name: "Андрій Трохимір", username: "troymer" },
    { name: "Олександр Бабкін", username: "babkin" },
    { name: "Аліна Кучер", username: "alinakucher" },
    { name: "Олександр Кучер", username: "kucher" },
  ]

  return (
    <ListGroup>
      {students.map((student, index) => (
        <ListGroup.Item key={index}>
          <div className="d-flex align-items-center justify-content-between">
            <div className="d-flex align-items-center">
              <Image src="https://via.placeholder.com/50" roundedCircle />
              <span className="ms-3">{student.name}</span>
              <span className="ms-2 text-muted">@{student.username}</span>
            </div>
            <div className="d-flex align-items-center">

              <Button variant="success" style={{width: 100}}>Rate</Button>
              <Button variant="danger" style={{width: 100}} className="ms-3">Remove</Button>
            </div>
          </div>
        </ListGroup.Item>
      ))}
    </ListGroup>
  )
}