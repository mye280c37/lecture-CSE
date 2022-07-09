const express = require('express');
const http = require('http');
const app = express();
const cors = require('cors');
const bodyParser = require('body-parser');

app.use(bodyParser.urlencoded({ extended: true }));
app.use(bodyParser.json())
app.use(cors());
app.set('port', process.env.PORT || 8001);

// express 서버 생성(8001번 포트)
http.createServer(app).listen(app.get('port'), function(){
    console.log('Express server listening on port ' + app.get('port'));
});

// 서버의 데이터는 빈 데이터로 초기화
let data = [

]

// 서버주소 뒤 /get 붙이면 res를 서버->클라이언트로 전송
app.use('/get', (req, res) => {
    res.send(data)
});

// 서버주소 뒤 /post 붙이면 req를 클라이언트->서버로 전송
app.use('/post', (req, res) => {
    const message = req.body.message
    const username = req.body.username
    const searched = req.body.searched

    data = [...data, {
        'message': message,
        'username': username,
        'searched' : searched,
    }]

    // 서버 실행 한 창에서 채팅 데이터 확인
    console.log(data)
});