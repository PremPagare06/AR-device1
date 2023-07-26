import speech_recognition as sr
import googletrans
import google_trans_new
import serial
r= sr.Recognizer()

input_lang = "hi"
output_lang = "fr"
ser = serial.Serial()                                           #make instance of Serial
ser.baudrate = 9600                                             #set baud to 9600 (9600b/s)
ser.port = "COM5"                                               #replace COM6 with your Arduino port; set serial port
ser.open()

while True:
    with sr.Microphone() as source:
            print("Listening....")
            audio = r.listen(source)
            
            try:

                speech_text= r.recognize_google(audio, language="mr")
                print(speech_text)
                if speech_text=="stop" :
                    break
            except sr.UnknownValueError:
                print("Could not understand")
            except sr.RequestError:
                print("Request Error")
            
            translator= googletrans.Translator()
            translation = translator.translate(speech_text, dest="en")
            print(translation.text)

            serialDataStr = str(translation.text)        #now we concenate all strings together by using "+" operand. By this, we´ll got one long string of data
            serialDataBytes = serialDataStr.encode("UTF-8")             #since we want to send string as series of BYTES, we wncode it to UTF-8 standart. This will put "b" before string, indicating that values are 1B each 

            print(serialDataBytes)                                      #here we print our serial string, used for debugging, can be commented out
            ser.write(serialDataBytes)                                  #send our long encoded string throught serial interface

ser.close()                                                     #this will never execute, because while loop will go forever. But i like to leave it here to prevent some bugs and bad stuff that could happen, also for you, if you want to include some way of getting out of the COM port



# print(googletrans.LANGUAGES)

