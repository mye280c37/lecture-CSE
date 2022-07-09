
import React, { Fragment } from "react";
import styled from "styled-components";
import ChatTemplate from "./components/ChatTemplate";

function App() {

	return (
    	<Fragment>
      		<Container>
        		<ChatTemplate />
     	 	</Container>
    	</Fragment>
	);
}

const Container = styled.div`
  display: flex;
  justify-content: center;
  align-items: center;
  text-align: center;
  min-height: 100vh;
`;

export default App


