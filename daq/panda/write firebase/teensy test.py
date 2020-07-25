while (True):
  teensy = serial.Serial('/dev/lexi', baudrate = 9600, timeout = 1)
  nano = serial.Serial('/dev/oliver', baudrate = 9600, timeout = 1)
  
  now = datetime.now()
  current_time = now.strftime("%H:%M:%S")
  previousTime = timeName
  timeName = current_time
  lapNumber = db.child("Lap").get()
  lapNumber = lapNumber.val()
  lapRunning = db.child("Running").get()
  lapRunning = lapRunning.val()
  
  teensyInput = teensy.readline().decode('ascii')
  if (teensyInput[0:3] == "Rpm"):
      newRPM = (teensyInput[5:10])
  teensyInput = teensy.readline().decode('ascii')
  if (teensyInput[0:3] == "Spd"):
      newSpeed = float(teensyInput[5:10])
  teensyInput = teensy.readline().decode('ascii')
  if (teensyInput[0:3] == "Lng"):
      newLong = float(teensyInput[5:10])
  teensyInput = teensy.readline().decode('ascii')
  if (teensyInput[0:3] == "Lat"):
      newLat = float(teensyInput[5:10])

  print(teensyInput)
  print(newRPM)
  print(newSpeed)
  print(newLong)
  print(newLat)
  
