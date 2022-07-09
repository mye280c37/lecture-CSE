import React, { useState } from "react";
import styled from "styled-components";
import TextField from "@material-ui/core/TextField";
import axios from 'axios';

// Sending Message 부분
function MessenagerTemplate({ getChatLog }) {
  const [MsgState, setMsgState] = useState({ message: "", username: "", searched: false })

  const onMsgChange = (e) => {
    setMsgState({ ...MsgState, [e.target.name]: e.target.value })
  }

  const onMsgSubmit = (e) => {
    // 1. 메시지 입력 창에서 빈 경우에는 ‘메시지를 입력하세요‘라는 내용의 경고 창 출력 후 리턴(alert 함수 사용)
    // 2. 사용자의 이름 입력 창이 빈 경우에는 사용자 이름을 ‘이름없음’으로 저장
    // 3. message와 username의 속성을 갖는 채팅 데이터를 axios.post 함수 사용하여 서버로 전송
    // (서버주소: http://localhost:8001, 메소드: post)
    
    e.preventDefault()

    // 9주차 실습 구현

    // 데이터를 보내는 동안 기다린 후 getChatLog 함수 실행
    setTimeout(getChatLog, 1000)
    // MsgState 초기화
    setMsgState({ message: "", username: "", searched: false })
  }

  return (
    <Form onSubmit={onMsgSubmit}>
      <Title>Sending Message</Title>
      <UserName>
        <TextField name="username" onChange={(e) => onMsgChange(e)} value={MsgState.username} label="User Name" />
      </UserName>
      <MessageContents>
        <TextField
          name="message"
          onChange={(e) => onMsgChange(e)}
          value={MsgState.message}
          id="outlined-multiline-static"
          variant="outlined"
          label="Message"
        />
      </MessageContents>
      <Button>Send</Button>
    </Form>
  );
}

const Title = styled.h1`
  margin: 10px;
  padding: 10px;
  border-radius: 5px;
  background-color: #d8b863;
  color: #ffffff;
`;

const Form = styled.form`
  width: 500px;
  margin: 10px;
  padding: 20px;
  border-radius: 5px;
  box-shadow: 0px 3px 24px -8px rgba(0, 0, 0, 0.75);
  background-color: #fffee4;
`;

const UserName = styled.div`
  margin: 40px;
`;

const MessageContents = styled.div`
  margin: 30px;
`;

const Button = styled.button`
  margin-top: 60px;
  padding: 10px;
  background-color: white;
  border-color: #c8a951;
  border-radius: 5px;
`;

export default MessenagerTemplate;