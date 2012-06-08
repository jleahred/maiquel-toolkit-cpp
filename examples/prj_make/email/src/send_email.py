#! /usr/bin/python

from smtplib import SMTP
import sys
import datetime

##debuglevel = 0

smtp = SMTP()
##smtp.set_debuglevel(debuglevel)
smtp.connect('100.100.16.130', 25)
smtp.login('jlesteban@grupocimd', 'Abril2011')

from_addr = "it"
date = datetime.datetime.now().strftime( "%d/%m/%Y %H:%M" )


##to_addr = "jlesteban@grupocimd.com"
##subj = "hello"
##message_text = "Hello\nThis is a mail from your server\n\nBye\n"


input = ''
line = ''
while True:
    line =  sys.stdin.readline()
    if line == '.END.\n':
        break
    input += line

exec (input)



msg = "From: %s\nTo: %s\nSubject: %s\nDate: %s\n\n%s" % ( from_addr, to_addr, subj, date, message_text )

smtp.sendmail(from_addr, to_addr, msg)
smtp.quit()

print "email sent ok"