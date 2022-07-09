import React from "react";
import styled from "styled-components";

import ChatLogItem from "./ChatLogItem";

// chats 배열을 받아 배열 안 각 chat 객체를 리스트로 보여 줌
function ChatLogTemplate({ chats, onSearchKeySubmit }) {

  return (
    <ChatContainer>
      {/* ChatSearch 컴포넌트 구현 후 추가 */}
      <h1>Chat Log</h1>
      {chats.map((chat, index) => {
        return <ChatLogItem chat={chat} key={index} />;
      })}
    </ChatContainer>
  );

}

const ChatContainer = styled.div`
  width: 500px;
  border-radius: 5px;
  margin: 10px;
  box-shadow: 0px 3px 24px -8px rgba(0, 0, 0, 0.75);
  background-color: #f3eaaf;
`;

export default ChatLogTemplate;