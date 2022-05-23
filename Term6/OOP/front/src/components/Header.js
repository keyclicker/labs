import Navbar from 'react-bootstrap/Navbar';
import Container from 'react-bootstrap/Container';

export default 
function Header(props) {
  return (
    <Navbar bg="dark" variant="dark" sticky="top">
      <Container fluid="xl" className="justify-content-between">
        <Navbar.Brand href="#home">udex.courses</Navbar.Brand>
        <Navbar.Toggle />
      
        <Navbar.Collapse className="justify-content-end">
          <Navbar.Text>
            Signed in as: <a href="#login">Mark Otto</a>
          </Navbar.Text>
        </Navbar.Collapse>
      </Container>
    </Navbar>
  )
}