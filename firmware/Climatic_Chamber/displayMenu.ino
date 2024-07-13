void displayMenu() {
  
  if (enc.left() || enc.right() || enc.click() || enc.hold()) {
    lastInteractionTime = millis();  // Reset the interaction timer
  }
  // Check for timeout
  if (currentScreen != MAIN && (millis() - lastInteractionTime >= timeoutDuration)) {
    currentScreen = MAIN;
    displayMainScreen();
  }
  switch (currentScreen) {
    case MAIN:
      if (enc.click()) {
        currentScreen = MENU;
        displayMenuScreen();
      }
      break;

    case MENU:
      if (enc.left()) {
        selectedMenuItem--;
        if (selectedMenuItem < 0) {
          selectedMenuItem = 3;                        // Wrap around to the last item
          topMenuItem = max(0, 3 - itemsPerPage + 1);  // Adjust top item for wrap-around
        } else if (selectedMenuItem < topMenuItem) {
          topMenuItem = selectedMenuItem;
        }
        displayMenuScreen();
      } else if (enc.right()) {
        selectedMenuItem++;
        if (selectedMenuItem > 3) {
          selectedMenuItem = 0;  // Wrap around to the first item
          topMenuItem = 0;       // Adjust top item for wrap-around
        } else if (selectedMenuItem >= topMenuItem + itemsPerPage) {
          topMenuItem = selectedMenuItem - itemsPerPage + 1;
        }
        displayMenuScreen();
      } else if (enc.click()) {
        if (selectedMenuItem == 0) {  // If "Configuration" is selected
          currentScreen = CONFIGURATION;
          displayConfigurationScreen();
        } else if (selectedMenuItem == 1) {
          currentScreen = SETUP;
          displaySetupScreen();
        } else if (selectedMenuItem == 2) {
          currentScreen = INFO;
          displayInfoScreen();
        } else if (selectedMenuItem == 3) {  // If the back button is selected
          currentScreen = MAIN;
          displayMainScreen();
        }
      } else if (enc.hold()) {
        currentScreen = MAIN;
        selectedSubMenuItem = 0;
        displayMainScreen();
      }
      break;

    case SETUP:
      if (enc.left()) {
        selectedSubMenuItem--;
        if (selectedSubMenuItem < 0) {
          selectedSubMenuItem = 3;  // Wrap around to the last item
        }
        displaySetupScreen();
      } else if (enc.right()) {
        selectedSubMenuItem++;
        if (selectedSubMenuItem > 3) {
          selectedSubMenuItem = 0;  // Wrap around to the first item
        }
        displaySetupScreen();
      } else if (enc.click()) {
        if (selectedSubMenuItem == 3) {  // If the back button is selected
          currentScreen = MENU;
          selectedSubMenuItem = 0;
          displayMenuScreen();
        } else if (selectedSubMenuItem == 0) {  // If "Temp. Offset" is selected
          currentScreen = TEMP_OFFSET;
         displayTempOffsetScreen();
        } else if (selectedSubMenuItem == 1) {  // If "Temp. Offset" is selected
          currentScreen = HUMIDITY_OFFSET;
          displayHumOffsetScreen();
        }
        // Handle other submenu items similarly...
      } else if (enc.hold()) {
        currentScreen = MENU;
        selectedSubMenuItem = 0;
        displayMenuScreen();
      }
      break;

    case TEMP_OFFSET:
      if (enc.left()) {
        mydata.tempOffset--;
        displayTempOffsetScreen();
      } else if (enc.right()) {
        mydata.tempOffset++;
        displayTempOffsetScreen();
      } else if (enc.click() || enc.hold()) {
        currentScreen = SETUP;
        displaySetupScreen();
      }
      break;

    case TEMP_CONTROL:
      if (enc.left()) {
        if (selectedTempControlItem == 0) {
          if (mydata.sw_temp) {
            mydata.sw_temp = false;
          } else {
            mydata.sw_temp = true;
          }
        } else if (selectedTempControlItem == 1) {
          mydata.temp--;
        } else if (selectedTempControlItem == 2) {
          mydata.temp_hys--;
        } else if (selectedTempControlItem == 3) {
          if (mydata.sw_tempmode) {
            mydata.sw_tempmode = false;
          } else {
            mydata.sw_tempmode = true;
          }
        }
        displayTempControlScreen();
      } else if (enc.right()) {
        if (selectedTempControlItem == 0) {
          if (mydata.sw_temp) {
            mydata.sw_temp = false;
          } else {
            mydata.sw_temp = true;
          }
        } else if (selectedTempControlItem == 1) {
          mydata.temp++;
        } else if (selectedTempControlItem == 2) {
          mydata.temp_hys++;
        } else if (selectedTempControlItem == 3) {
          if (mydata.sw_tempmode) {
            mydata.sw_tempmode = false;
          } else {
            mydata.sw_tempmode = true;
          }
        }
        displayTempControlScreen();
      } else if (enc.click()) {
        selectedTempControlItem++;
        if (selectedTempControlItem > 3) {
          selectedTempControlItem = 0;
        }
        displayTempControlScreen();
      } else if (enc.hold()) {
        currentScreen = CONFIGURATION;
        displayConfigurationScreen();
      }
      break;

    case HUM_CONTROL:
      if (enc.left()) {
        if (selectedHumControlItem == 0) {
          if (mydata.sw_humidity) {
            mydata.sw_humidity = false;
          } else {
            mydata.sw_humidity = true;
          }
        } else if (selectedHumControlItem == 1) {
          mydata.set_humidity--;
        } else if (selectedHumControlItem == 2) {
          mydata.humidity_hys--;
        }
        displayHumControlScreen();
      } else if (enc.right()) {
        if (selectedHumControlItem == 0) {
          if (mydata.sw_humidity) {
            mydata.sw_humidity = false;
          } else {
            mydata.sw_humidity = true;
          }
        } else if (selectedHumControlItem == 1) {
          mydata.set_humidity++;
        } else if (selectedHumControlItem == 2) {
          mydata.humidity_hys++;
        }
        displayHumControlScreen();
      } else if (enc.click()) {
        selectedHumControlItem++;
        if (selectedHumControlItem > 2) {
          selectedHumControlItem = 0;
        }
        displayHumControlScreen();
      } else if (enc.hold()) {
        currentScreen = CONFIGURATION;
        displayConfigurationScreen();
      }
      break;
    case DRAIN_CONTROL:
      if (enc.left()) {
        if (selectedDrainControlItem == 0) {
          if (mydata.sw_draining) {
            mydata.sw_draining = false;
          } else {
            mydata.sw_draining = true;
          }
        } else if (selectedDrainControlItem == 1) {
          mydata.set_draining--;
        } else if (selectedDrainControlItem == 2) {
          mydata.draining_hys--;
        }
        displayDrainingControlScreen();
      } else if (enc.right()) {
        if (selectedDrainControlItem == 0) {
          if (mydata.sw_draining) {
            mydata.sw_draining = false;
          } else {
            mydata.sw_draining = true;
          }
        } else if (selectedDrainControlItem == 1) {
          mydata.set_draining++;
        } else if (selectedDrainControlItem == 2) {
          mydata.draining_hys++;
        }
        displayDrainingControlScreen();
      } else if (enc.click()) {
        selectedDrainControlItem++;
        if (selectedDrainControlItem > 2) {
          selectedDrainControlItem = 0;
        }
        displayDrainingControlScreen();
      } else if (enc.hold()) {
        currentScreen = CONFIGURATION;
        displayConfigurationScreen();
      }
      break;
    
    case A_CIRCUL_CONTROL:
      if (enc.left()) {
        if (selectedACirculControlItem == 0) {
          if (mydata.sw_a_circulation) {
            mydata.sw_a_circulation = false;
          } else {
            mydata.sw_a_circulation = true;
          }
        } else if (selectedACirculControlItem == 1) {
          mydata.air_circulation_Period = constrain(mydata.air_circulation_Period - 1, 0, 24);
        } else if (selectedACirculControlItem == 2) {
          mydata.air_circulation_Duration = constrain(mydata.air_circulation_Duration - 1, 0, 60);
        } else if (selectedACirculControlItem == 3) {
          mydata.air_circulation_fan_pwr = constrain(mydata.air_circulation_fan_pwr - 10, 0, 100);
        }
        displayACirculControlScreen();
      } else if (enc.right()) {
        if (selectedACirculControlItem == 0) {
          if (mydata.sw_a_circulation) {
            mydata.sw_a_circulation = false;
          } else {
            mydata.sw_a_circulation = true;
          }
        } else if (selectedACirculControlItem == 1) {
          mydata.air_circulation_Period = constrain(mydata.air_circulation_Period + 1, 0, 24);
        } else if (selectedACirculControlItem == 2) {
          mydata.air_circulation_Duration = constrain(mydata.air_circulation_Duration + 1, 0, 60);
        } else if (selectedACirculControlItem == 3) {
          mydata.air_circulation_fan_pwr = constrain(mydata.air_circulation_fan_pwr + 10, 0, 100);
        }
        displayACirculControlScreen();
      } else if (enc.click()) {
        selectedACirculControlItem++;
        if (selectedACirculControlItem > 3) {
          selectedACirculControlItem = 0;
        }
        displayACirculControlScreen();
      } else if (enc.hold()) {
        currentScreen = CONFIGURATION;
        displayConfigurationScreen();
      }
      break;

    case HUMIDITY_OFFSET:
      if (enc.left()) {
        mydata.humidityOffset--;
        displayHumOffsetScreen();
      } else if (enc.right()) {
        mydata.humidityOffset++;
        displayHumOffsetScreen();
      } else if (enc.click() || enc.hold()) {
        currentScreen = SETUP;
        displaySetupScreen();
      }
      break;

    case CONFIGURATION:
      if (enc.left()) {
        selectedSubMenuItem--;
        if (selectedSubMenuItem < 0) {
          selectedSubMenuItem = 5;                        // Wrap around to the last item
          topSubMenuItem = max(0, 5 - itemsPerPage + 1);  // Adjust top item for wrap-around
        } else if (selectedSubMenuItem < topSubMenuItem) {
          topSubMenuItem = selectedSubMenuItem;
        }
        displayConfigurationScreen();
      } else if (enc.right()) {
        selectedSubMenuItem++;
        if (selectedSubMenuItem > 5) {
          selectedSubMenuItem = 0;  // Wrap around to the first item
          topSubMenuItem = 0;       // Adjust top item for wrap-around
        } else if (selectedSubMenuItem >= topSubMenuItem + itemsPerPage) {
          topSubMenuItem = selectedSubMenuItem - itemsPerPage + 1;
        }
        displayConfigurationScreen();
      } else if (enc.click()) {
        if (selectedSubMenuItem == 5) {  // If the back button is selected
          currentScreen = MENU;
          selectedSubMenuItem = 0;
          topSubMenuItem = 0;
          displayMenuScreen();
        } else if (selectedSubMenuItem == 0) {  // If "Temperature Control" is selected
          currentScreen = TEMP_CONTROL;
          displayTempControlScreen();
        } else if (selectedSubMenuItem == 1) {  // If "Temperature Control" is selected
          currentScreen = HUM_CONTROL;
          displayHumControlScreen();
        } else if (selectedSubMenuItem == 2) {  // If "Temperature Control" is selected
          currentScreen = DRAIN_CONTROL;
          displayDrainingControlScreen();
        }else if (selectedSubMenuItem == 3) {  // If "Temperature Control" is selected
          currentScreen = A_CIRCUL_CONTROL;
          displayACirculControlScreen();
        }
        // Add specific actions for each configuration item if needed
      } else if (enc.hold()) {
        currentScreen = MENU;
        selectedSubMenuItem = 0;
        topSubMenuItem = 0;
        displayMenuScreen();
      }
      break;

    case INFO:
      if (enc.left()) {
        selectedSubMenuItem--;
        if (selectedSubMenuItem < 0) {
          selectedSubMenuItem = 4;                        // Wrap around to the last item
          topSubMenuItem = max(0, 4 - itemsPerPage + 1);  // Adjust top item for wrap-around
        } else if (selectedSubMenuItem < topSubMenuItem) {
          topSubMenuItem = selectedSubMenuItem;
        }
        displayInfoScreen();
      } else if (enc.right()) {
        selectedSubMenuItem++;
        if (selectedSubMenuItem > 4) {
          selectedSubMenuItem = 0;  // Wrap around to the first item
          topSubMenuItem = 0;       // Adjust top item for wrap-around
        } else if (selectedSubMenuItem >= topSubMenuItem + itemsPerPage) {
          topSubMenuItem = selectedSubMenuItem - itemsPerPage + 1;
        }
        displayInfoScreen();
      } else if (enc.click()) {
        if (selectedSubMenuItem == 4) {  // If the back button is selected
          currentScreen = MENU;
          selectedSubMenuItem = 0;
          topSubMenuItem = 0;
          displayMenuScreen();
        }
      } else if (enc.hold()) {
        currentScreen = MENU;
        selectedSubMenuItem = 0;
        topSubMenuItem = 0;
        displayMenuScreen();
      }
      break;
  }
 
}