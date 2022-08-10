import cv2
import pyrebase

firebaseConfig = {
    'apiKey': "AIzaSyD1Ts2a8SCOKWBm8Ncl2nrSxwqU_QJ-Je4",
    'authDomain': "detaintp.firebaseapp.com",
    'databaseURL': "https://detaintp-default-rtdb.firebaseio.com",
    'projectId': "detaintp",
    'storageBucket': "detaintp.appspot.com",
    'messagingSenderId': "383914364000",
    'appId': "1:383914364000:web:66e7473861ba9b451a0705",
    'measurementId': "G-78XXC6R60Y"
}

firebase = pyrebase.initialize_app(firebaseConfig)
auth = firebase.auth()
email = "datquan@mail.com"
password = "123456"
auth.sign_in_with_email_and_password(email, password)

face_cascade = cv2.CascadeClassifier("haarcascade_frontalface_default.xml")
cap = cv2.VideoCapture("http://10.2.22.130:81/stream")
# cap = cv2.VideoCapture(0)

while True:
    db = firebase.database()
    ct = {}
    ret, frame = cap.read()  
    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
    faces = face_cascade.detectMultiScale(gray)
    
    for (x, y, w, h) in faces:
        cv2.rectangle(frame, (x, y), (x+w, y+h), (0, 255, 0), 2)
        ct["controlall"] = True
        db.child("ct").update(ct)
        
    cv2.imshow("Detecting face", frame)
    ct["controlall"] = False
    db.child("ct").update(ct)
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

cap.release()
cv2.destroyAllWindows