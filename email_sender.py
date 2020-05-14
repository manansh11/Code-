import smtplib
from email.message import EmailMessage


#Create EmailMessage Object (Instantiate)
email = EmailMessage()
email['from'] = 'Your Name'
email['to'] = 'hello@gmail.com'
email['subject'] = 'Hello' 

#Content of email
email.set_content('Write a message here')

with smtplib.SMTP(host='smtp.gmail.com', port=587) as smtp:
    smtp.ehlo()
    smtp.starttls() #Encryption Mechanism
    smtp.login('gmail@gmail.com', 'password')
    smtp.send_message(email)
    print("Email Sent")
