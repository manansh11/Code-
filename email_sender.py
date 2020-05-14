import smtplib
from email.message import EmailMessage


#Create EmailMessage Object (Instantiate)
email = EmailMessage()
email['from'] = 'Manansh Shukla'
email['to'] = 'divy32@outlook.com'
email['subject'] = 'Hello' 

#Content of email
email.set_content('You are gay')

with smtplib.SMTP(host='smtp.gmail.com', port=587) as smtp:
    smtp.ehlo()
    smtp.starttls() #Encryption Mechanism
    smtp.login('calgarycartcorp@gmail.com', 'heythecarthasfourrings11!')
    smtp.send_message(email)
    print("Email Sent")
