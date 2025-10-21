from datetime import datetime, timezone
from time import time
unix_now = time()

# unix_time_input eg = 1713171600

user_prefer = input("1.Terminal \n2.try GUI(tkinter)\n Select :")

if user_prefer == "1":
    
    print("[INFO] type '-1' to exit")
    while True:
        
        #CUI
        unix_time = input(" Unix Time : ")
        
        try:
            unix_time = int(unix_time)
        except:
            print("[Error]Check your input.")
            continue 

        if unix_time == -1:
            break 
        elif len(str(unix_time)) > 10:
            print("[Error]Check your input.")
            continue
        
        sys_time = datetime.fromtimestamp(unix_time)
        utc_time = str(datetime.fromtimestamp(unix_time, timezone.utc)).split("+")[0]
        print("[Result]")
        print(f"{utc_time} : UTC time \n{sys_time} : Your System ")


elif user_prefer == "2":
    
    # tkinter- GUI
    from tkinter import *

    #function
    def convert():
        # Get data
        input_time = float(utc_entry.get())
        result_time = datetime.fromtimestamp(input_time)
        result_utc_time = str(datetime.fromtimestamp(input_time, timezone.utc)).split("+")[0]
        
        # Update label
        print_time.config(text=result_time)
        print_utc_time.config(text=result_utc_time)
        
    #UI
    window = Tk()
    window.title("Unix Time Converter")
    window.config(padx=10,pady=10)

    utc_entry = Entry(text="UNIX_TIME", width=25)
    utc_entry.grid(column=0,row=0)
    utc_entry.insert(0, unix_now)

    convert_button = Button(text="Convert", width=25, command=convert, highlightthickness=0)
    convert_button.grid(column=0, row=1)

    label_utc_time = Label(text="UTC Time")
    label_utc_time.grid(column=0, row=2)
    
    print_utc_time = Label()
    print_utc_time.grid(column=0, row=3)

    label_time = Label(text ="Your System")
    label_time.grid(column=0, row=4)
    
    print_time = Label()
    print_time.grid(column=0, row=5)
    window.mainloop()
    
else:
    pass