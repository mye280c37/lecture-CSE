import React, { useState, useEffect } from "react";
import styled from "styled-components";
import axios from 'axios';
import MessenagerTemplate from "./MessengerTemplate";
import ChatLogTemplate from "./ChatLogTemplate";

// 전체를 감싸는 컴포넌트
function ChatTemplate() {
	const [chats, setChats] = useState([])
	const [chat_len, setChatLen] = useState(0)

	// 새 창을 열거나 새로고침 실행 시, getChatLog()를 함수 사용하여 chats의 내용을 업데이트
	useEffect(
		() => {
			getChatLog()
		},
		[chats]
	)

	const getChatLog = () => {
		// 1. axios.get 함수를 사용해서 채팅 데이터 가져오기 (서버주소: http://localhost:8001, 메소드: get)
		// 2. chats 배열에 가져온 데이터 저장
		// 3. 가져온 데이터의 길이, 현재 chat_len 비교해서 chats 업데이트
		// 2,3번 구현 시 axios.get의 callback 함수 then((res)=>{}) 사용하여 구현
		
		// 9주차 실습 구현
	}

	// 키워드 검색 시 keyword를 검색창에 입력했을 때, 호출되는 함수
	const onSearchKeySubmit = (keyword) => {
		// 9주차 실습 구현
	}

	return (
		<Container>
			<MessenagerTemplate getChatLog={getChatLog} />
			<ChatLogTemplate chats={chats} onSearchKeySubmit={onSearchKeySubmit} />
		</Container>
	);
}

const Container = styled.div`
  display: grid;
  grid-template-columns: 1fr 1fr;
  margin: 10px;
  min-height: 30rem;
`;

export default ChatTemplate;