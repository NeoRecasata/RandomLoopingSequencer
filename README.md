# RandomLoopingSequencer
A random looping sequencer built with an Arduino Nano. <br> Highly inspired by Tom Whitwell's Turing Machine Eurorack Module.

## Features

1. Clock input
2. 2 to 16 steps (2,3,4,5,6,8,12,16)
3. Random CV output with randomness potentiometer
4. CV step erase
5. Random trigger with probability potentiometer
6. Trigger step erase

## TODO
- [x] 1. Step length Potentiometer
- [x] 2. MCP-4725 voltage output for CV
- [x] 3. Schematic
- [ ] 4. Board

## Latest Files
[Schematic](https://github.com/NeoRecasata/RandomLoopingSequencer/blob/main/Latest%20Revision/Random%20Looping%20Sequencer%20Rev4.pdf) <br>
[Arduino File](https://github.com/NeoRecasata/RandomLoopingSequencer/blob/main/Latest%20Revision/Random_Looping_Sequencer.ino)

## I/O
### Inputs
All inputs are protected. <br>
| Input               | Voltage Standard |
|---------------------|------------------|
| CV probability      | 10vpp            |
| Trigger probability | 10vpp            |
| Clock               | 0-5v             |

### Outputs
| Output  | Voltage Standard | Pulse Duration |
|---------|------------------|----------------|
| CV      | 0-5v             | N/A            |
| Trigger | 0-5v             | 12ms           |

## Demo
Coming soon!
