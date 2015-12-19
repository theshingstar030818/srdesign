Senior Design Repository
========================
Our goal is to implement real-time software controller to simulate an Insulin Pump. The project will be written in C, using many of the pre-defined ARM/LPC17xx libraries as a starting point.   
   
**Hardware:**
   * Keil MCB1760UME - Development board used, features Cortex-M3 ARM microprocessor
   * Linear Actuator - Used as the administration mechanism to deliver the insulin
   * Syringe - Used as the holder for the insulin that the Linear Actuator will push
   
**Software:**
   * Keil uVision 5 - IDE used for software development
   * Git - VCS/SCM used to track and review development

Primary Goals:
--------------
  * Interface MCB Development Board with Linear Actuator using GPIO
  * Interface Linear Actuator with Syringe
  * Implement Functional Basal Dose (*Continuous Dose Over Time*)
  * Implement Functional Bolus Dose (*One Time User-Initiated Dose*)
  * Implement Security Features that apply as specified in [Security Requirements](http://www.ncbi.nlm.nih.gov/pmc/articles/PMC3262707/)

Secondary Goals:
----------------
  * Interface MCB1700 with Continuous Glucose Montior using GPIO
  * Set-up MCB1700 to be able to read/write to micro SD Card
  * Implement Security Features that apply to the additional features
  
Keil uVision Set-Up:
--------------------
   1. Project -> New uVision Project... 
   2. Choose a name and folder for your workspace
   3. Choose NXP -> LPC1700 Series -> LPC176x -> LPC1768 -> OK
   4. Choose the following Software Components in the Manage Run-Time Environment:
      * Board Support
         * Graphic LCD (API) -> Graphic LCD
         * LED (API) -> LED
      * CMSIS
         * CORE
      * CMSIS Driver
         * SPI (API) -> SSP
      * Device
         * GPDMA
         * GPIO
         * PIN
         * Startup
      * Press Resolve if necessary and then OK
   5. Copy all of the files in the git repository over to the workspace (include the .git folder)
   6. Right-click on 'Source Group 1' folder and click "Add Existing Files to group 'Source Group 1'..."
      * Add all of the files from the git repository
   7. Right-click on one of the added files, and click 'Rebuild all target files'
   8. Libraries will populate. Expand 'Device' option and open up 'RTE_Device.h'
      * Click on 'Configuration Wizard' at the bottom of the code window
      * Make sure that 'SSP1 (Synchronous Serial Port 1) [Driver_SPI1]' is checked.
   9. Recompile the code (Step 7)
