""" This class is created to output a constant **Python List** vairable.
    It simulates the DaVinciXiAPI functions.
    Author: Mustafa UGUR  Date: 08/08/2019
    """

import time
import threading
import string

class fakeDaVinciXiAPI:
  def __init__(self):
    self.outputList = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]
    self.x = threading.Thread(target=self.changeJointValues)
    self.x.start()

  def get_usm_joint_values(self):
    return self.outputList

  def changeJointValues(self):
    while True:
      self.outputList[-1] += 1
      time.sleep(0.5)


