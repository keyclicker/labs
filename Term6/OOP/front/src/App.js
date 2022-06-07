import Container from 'react-bootstrap/Container';
import Col from 'react-bootstrap/Col';
import Row from 'react-bootstrap/Row';

import CourseCard from './components/CourseCard';
import FiltersCard from './components/FiltersCard';
import Header from './components/Header';

import { useEffect, useState } from 'react';
import { client } from './api/api';
import { CourseCreator } from './components/CourseCreator';
import Button from 'react-bootstrap/esm/Button';

function App() {
  const [query, setQuery] = useState('');
  const [user, setUser] = useState(null);
  const [courses, setCourses] = useState([]);
  const [showCreator, setShowCreator] = useState(false);

  useEffect(() => {
    client.get('/session').then(res => {
      setUser(res.data.user);
    });
  }, []);

  useEffect(() => {
    client.get(`/search?q=${query}`).then((response) => {
      setCourses(response.data);
    })
  }, [query]);

  console.log(courses);
  const state = {
    query, setQuery,
    user, setUser,
    courses, setCourses,
    showCreator, setShowCreator
  }

  return (
    <>
      <Header state={state}/>
      <Container fluid="xl">
        <Row className="mt-3 ">
            <Col>
            {state?.user?.type == 0 && showCreator &&
              <CourseCreator state={state}/>}

            {courses.map((c, i) => (
                <CourseCard key = {c.id} state={state} course={c}/>
            ))}

            {courses.length === 0 && 
            <h3 className='text-center mt-4 text-muted'>
              Курси не знайдено
            </h3>}

            </Col>
            <Col xs={{span: 12, order: "first"}} 
                 lg={{span: 3, order: "last"}}>
              <FiltersCard state={state}/>
              {state?.user?.type == 0 && !showCreator &&
                <Button className='w-100' onClick={()=>setShowCreator(true)}>
                  Створити курс</Button>}
            </Col>
        </Row>
      </Container>

    </>
  );
}

export default App;
