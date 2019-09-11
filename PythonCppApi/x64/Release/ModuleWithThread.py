import time
import threading


class ClassWithThread:
  def __init__(self):
    self.value = [1, 2, 3]
    self.thread = threading.Thread(target=self.incrementValue)
    self.thread.start()
    
  def incrementValue(self):
    while True:
      val0 = self.value[0]
      val1 = self.value[1]
      val2 = self.value[2]
      self.value = [val2, val0, val1]
      time.sleep(0.01)
      
  def getValue(self):
    return self.value
