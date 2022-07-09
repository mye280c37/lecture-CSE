import React from "react";
import styled from "styled-components";

// chat 객체 하나를 인자로 받아 한 줄로 표현하기 위한 컴포넌트
function ChatLogItem({ chat }) {
  return (
    <div>
      <UsernameContainer searched={chat.searched}>
        {chat.username}<ChatContainer searched={chat.searched}>: {chat.message}</ChatContainer>
      </UsernameContainer>
    </div>
  );

}

const UsernameContainer = styled.h3`
  color: ${props => props.searched ? 'red' : '#bda55d'}
`;

const ChatContainer = styled.span`
  color: ${props => props.searched ? 'red' : 'black'}
`;

export default ChatLogItem;