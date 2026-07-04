# EdgeAI-Contactless-Gesture-Controller
A lightweight, real-time TinyML gesture controller deployed on an STM32 microcontroller. The system captures spatial-temporal data from a Time-of-Flight (ToF) distance sensor, tracks human intent using a local LSTM neural network, and emulates a native USB hardware mouse—completely offline and driverless.
# 🛠️ The Core Pipeline (How It Works)
The system operates as an end-to-end processing conveyor belt running inside a tight FreeRTOS execution loop:
FIFO Ingestion: Reads single distance values from the ToF sensor via I2C, pushing them into a rolling 30-sample sliding window queue.
Noise Scrubbing: An in-line C filter automatically discards out-of-range sensor spikes (1200mm timeout errors) before data hits the AI.
LSTM Inference: The clean data pointer is processed locally by the X-CUBE-AI runtime engine to calculate the vector trajectory of the hand.
Dual Output: Valid swipes instantly dual-route to parallel hardware channels:
USB HID Engine: Moves the PC cursor (Left Swipe) or triggers a context menu click (Right Swipe) without any background PC drivers.
UART Channel: Streams live diagnostic tracking metrics to the serial monitor.
# 💾 Resource FootprintOptimized for constrained embedded hardware layouts
SRAM (Live RAM) ~6–12 KB: Handles task stacks, ToF sliding buffers, and the AI activation mathematical workspace. Includes protected memory sizing to prevent buffer overflows.
Flash (ROM) ~60–100 KB: Permanently stores the LSTM network weights (const arrays), the FreeRTOS kernel, and the USB configuration stack.
# 🚀 Key Optimization Wins
Zero-Latency Execution: Prioritized time-critical USB packet delivery ahead of character-formatting string logs, dropping system latency down to 1ms.
Hardware Trajectory Latching: Implemented an explicit 10ms OS state latch for the right-click button mask, ensuring 100% reliable click registration on host operating systems.
Decoupled USB Architecture: Separated the ST-LINK debugging interface logic from the MCU's internal Full-Speed native USB differential physical lanes (D+/D−).
