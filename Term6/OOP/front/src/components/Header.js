import Navbar from 'react-bootstrap/Navbar';
import Container from 'react-bootstrap/Container';
import Button from 'react-bootstrap/esm/Button';
import { LoginModal, SignupModal } from './AuthModals';
import { useState } from 'react';
import Popover from 'react-bootstrap/Popover';
import OverlayTrigger from 'react-bootstrap/OverlayTrigger';
import { client } from '../api/api';

export default 
function Header({state}) {
  const [showSignup, setShowSignup] = useState(false);
  const [showLogin, setShowLogin] = useState(false);

  const logout = () => {
    client.post('/logout').then(res => {
      state.setUser(null);
    })
  }

  const popover = (
    <Popover id="popover-basic">
      <Popover.Header as="h3">{state?.user?.name}</Popover.Header>
      <Popover.Body>
        <div className='text-center mb-3'>{state?.user?.type ? 'Student' : 'Professor'}</div>

        <Button variant="primary" 
                onClick={logout}>
                    Log Out
                </Button>
      </Popover.Body>
    </Popover>
  );

  return (
    <>
      <Navbar bg="dark" variant="dark" sticky="top">
        <Container fluid="xl" className="justify-content-between">
          <Navbar.Brand href="#home">udex.courses</Navbar.Brand>
          <Navbar.Toggle />
          <Navbar.Collapse className="justify-content-end">
            {
              state.user 
              ? <Navbar.Text>
                  <OverlayTrigger trigger="click" placement="bottom" overlay={popover}>
                    <span role="button" className='user-select-none'>
                      {state.user.username}</span>
                  </OverlayTrigger>
         
              </Navbar.Text>
              : <>
                <Button variant="primary" 
                onClick={()=>setShowSignup(true)}>
                    Sign Up
                </Button>
                <Button variant="light" className="ms-3" 
                onClick={()=>setShowLogin(true)}>
                    Log In
                </Button> 
              </>
            }
          </Navbar.Collapse>
        </Container>
      </Navbar>

      <SignupModal state={state} show={showSignup} close={() => setShowSignup(false)}/>
      <LoginModal state={state} show={showLogin} close={() => setShowLogin(false)}/>
    </>
  )
}