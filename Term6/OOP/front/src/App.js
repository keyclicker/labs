import Container from 'react-bootstrap/Container';
import Col from 'react-bootstrap/Col';
import Row from 'react-bootstrap/Row';

import CourseCard from './components/CourseCard';
import FiltersCard from './components/FiltersCard';
import Header from './components/Header';

import { useState } from 'react';
import { client } from './api/api';

function App() {
  const [query, setQuery] = useState('');
  const [user, setUser] = useState(null);
  const [courses, setCourses] = useState([]);

  const handleQueryChange = (query) => {
    client.get(`/search?q=${query}`).then((response) => {
      setCourses(response.data);
    })

    setQuery(query);
    console.log(courses);
  }

  console.log(courses);
  const state = {
    query, setQuery,
    user, setUser,
    handleQueryChange,
  }

  return (
    <>
      <Header/>
      <Container fluid="xl">
        <Row className="mt-3 ">
            <Col>
            {
              courses.map((c, i) => (
                <CourseCard key = {c.id} state={state} course={c}/>
              ))
            }
            </Col>
            <Col xs={{span: 12, order: "first"}} 
                 lg={{span: 3, order: "last"}}>
              <FiltersCard state={state}/>
            </Col>
        </Row>
      </Container>

    </>
  );
}

export default App;
