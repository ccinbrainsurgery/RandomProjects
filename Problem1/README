Problem 1 : Given a list of people with their birth and end years (all between 1900 and 2000), find the year with the most number of people alive.


The problem definition is a bit vague.
So I am making the following Assumptions : 
- Number of people is given as input to create a random dataset on the fly
  - Name of a person is randomly generated.
  - Born year is randomly generated to be between (1900 and 1950).
  - Dead year is randomly generated with born year + a randomly generated age (between 60 and 90).
  - If 'Dead' year exceeds 2000 I am assigning it 'NULL' and assuming the person is alive regardless of the current year. 

- Current year is given as input to complete the defintion of a 'Person being alive'
  - Current definition is if(dead year is NULL or dead year > current year)
  - Previous definition was just (if dead year > current year), the dataset could have ages > 2000 though.
- The branch that outputs 'No one is alive' never gets called, after I updated my definitions of 'Person being alive', but I have tested it using previous definition. I have left it in there just for demonstration.

Notes :
- There are two versions of the main algorithm : one non-optimized and one optimized.
- I have added a performacne measurement code to demonstrate the effect of the optimization.

Output :

SampleOutput.txt - gives some examples of inputs and output to the program.
