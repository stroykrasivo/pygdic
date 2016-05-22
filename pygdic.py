#!/usr/bin/env python

from grab import Grab
from Tkinter import *
dlstr=48
ostr=""
def button_clicked():
	word.destroy()

word=Tk()
word.title=''
word.state='iconic'

#word.iconify()
#word.withdraw()
mword = word.selection_get()





g=Grab()
g.request(log_file="/tmp/pygdic.log", url="http://translate.google.com/translate_t?hl=ru&langpair=auto|ru&text="+mword)
autp=g.css_text('span#result_box')
trancecript=g.css_text('div#src-translit')

outplen=len(autp)/dlstr
for i in xrange(outplen+1):
	ostr+=autp[dlstr*i:dlstr*(i+1)]+"\n"


label= Label(word,width=dlstr+2, text = ostr+"\n"+trancecript , font="Arial 14", bg="#ffffaa",fg="blue")
label.pack(expand=True)
word.mainloop()
print autp,trancecript

exit()
