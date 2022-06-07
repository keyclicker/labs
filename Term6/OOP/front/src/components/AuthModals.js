import Button from 'react-bootstrap/Button';
import Modal from 'react-bootstrap/Modal';
import Form from 'react-bootstrap/Form';
import { useState } from 'react';
import { client } from '../api/api';

export function LoginModal({state, show, close}) {
  const [username, setUsername] = useState('');
  const [password, setPassword] = useState('');
  const [wrong, setWrong] = useState(false);

  const onLogin = () => {
    client.post('/login', {username, password}).then(res => {
      if (res?.data?.user) {
        state.setUser(res.data.user);
      } else {
        setWrong(true);
      }
      close();
    }
  )}

  const disabled = username.length < 4 || password.length  < 4;

  return (
    <Modal show={show} onHide={close}>
      <Modal.Header closeButton>
        <Modal.Title>Log In</Modal.Title>
      </Modal.Header>
      <Modal.Body>
        <Form>
          <Form.Group className="mb-3" controlId="formBasicEmail">
            <Form.Label>Username</Form.Label>
            <Form.Control type="Username" placeholder="Enter email"
            value={username} onChange={e=>setUsername(e.target.value)}/>
          </Form.Group>
          <Form.Group className="mb-3" controlId="formBasicPassword">
            <Form.Label>Password</Form.Label>
            <Form.Control type="password" placeholder="Password" 
            value={password} onChange={e=>setPassword(e.target.value)}/>
          </Form.Group>
        </Form>
      </Modal.Body>
      <Modal.Footer>
        <Button variant="primary" disabled={disabled} onClick={onLogin}>
          Log In
        </Button>
      </Modal.Footer>
    </Modal>
  )
}

export function SignupModal({state, show, close}) {
  const [username, setUsername] = useState('');
  const [name, setName] = useState('');
  const [type, setType] = useState(-1);
  const [password, setPassword] = useState('');
  const [password2, setPassword2] = useState('');
  const [wrong, setWrong] = useState(false);

  const onSignup = () => {
    client.post('/signup', {username, name, type, password}).then(res => {
      if (res?.data?.user) {
        state.setUser(res.data.user);
      } else {
        setWrong(true);
      }
      close();
    }
  )}

  const disabled = username.length < 4 || password.length < 4 || 
  password !== password2 || name.length < 2 || type === -1;

  return (
    <Modal show={show} onHide={close}>
      <Modal.Header closeButton>
        <Modal.Title>Sign Up</Modal.Title>
      </Modal.Header>
      <Modal.Body>
        <Form>
          <Form.Group className="mb-3" controlId="formBasicUsername">
            <Form.Label>Username</Form.Label>
            <Form.Control type="username" placeholder="Username"
            value={username} onChange={e=>setUsername(e.target.value)}/>
          </Form.Group>
          <Form.Group className="mb-3" controlId="formBasicFullName">
            <Form.Label>Full name</Form.Label>
            <Form.Control type="name" placeholder="Full name"
            value={name} onChange={e=>setName(e.target.value)}/>
          </Form.Group>
          <Form.Group className="mb-3" controlId="formBasicSelect">
            <Form.Label>Type</Form.Label>
            <Form.Select aria-label="Professor/Student"
            value={type} onChange={e=>setType(e.target.value)}>
              <option value={-1}>Professor/Student</option>
              <option value={0}>Professor</option>
              <option value={1}>Student</option>
            </Form.Select>
          </Form.Group>
          <Form.Group className="mb-3" controlId="formBasicPassword">
            <Form.Label>Password</Form.Label>
            <Form.Control type="password" placeholder="Password" 
            value={password} onChange={e=>setPassword(e.target.value)}/>
          </Form.Group>
          <Form.Group className="mb-3" controlId="formBasicPassword2">
            <Form.Label>Repeat password</Form.Label>
            <Form.Control type="password" placeholder="Repeat password" 
            value={password2} onChange={e=>setPassword2(e.target.value)}/>
          </Form.Group>
        </Form>
      </Modal.Body>
      <Modal.Footer>
        <Button variant="primary" onClick={onSignup} disabled={disabled}>
          Sign Up
        </Button>
      </Modal.Footer>
    </Modal>
  )
}