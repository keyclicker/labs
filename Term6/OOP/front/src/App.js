import Container from 'react-bootstrap/Container';
import Col from 'react-bootstrap/Col';
import Row from 'react-bootstrap/Row';

import CourseCard from './components/CourseCard';
import FiltersCard from './components/FiltersCard';
import Header from './components/Header';


function App() {
  return (
    <>
      <Header/>

      <Container fluid="xl">
        <Row className="mt-3 ">
            <Col>
            {
              Array(10).fill(0).map((_, i) => (
                <CourseCard/>
              ))
            }
            </Col>
            <Col xs={{span: 12, order: "first"}} 
                 lg={{span: 3, order: "last"}}>
              <FiltersCard/>
            </Col>
        </Row>
      </Container>

    </>
  );
}



export default App;
