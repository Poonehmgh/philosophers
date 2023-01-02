# philosophers
# 1. What is the problem?
There are n number of philosophers around a table, and they have to live along. For each philosopher to live, there is a simple rule: to not starve. 
This is like real life, isn't it?


but starvation has a measure here. A time is provided to our program that tells us the maximum time of starvation: the maximum time, that is passed from the certain philosopher's start of the meal. (or if has'nt eaten yet, from the start of program).
the problem is that each philospher needs two fork for eating food. so each of them has to grab the neighbouring person's fork to be able to eat. 
but if all of them do that, what happens? no one would be able to eat because everyone has took their personal fork and no second fork is left for anyone. 
This is what we should avoid.
# 2. What should you do in this project? 
We are faced with a challenge here. To provide an algorithm that lets our philosophers eat the most possible time.
# 3. How do we test that our program is working? 
with a look to the eval sheet, we see: 
  <img width="980" alt="Screen Shot 2022-12-16 at 1 30 18 PM" src="https://user-images.githubusercontent.com/100726824/209474901-8c6d48c7-0623-4c9b-a871-66ca76c19052.png">

from this we can conclude: 
	- the eating time * 2 <= die time, it means that all the philosophers should be able to eat and no one should die. (why? because each time half of philos can eat and their sideby side phio cant since they lended their fork. so at least 2 * eat time is required for everyone to get a meal.)
	- if the number of philosophers are odd, one phiosopher is always left out. so we need at least 3 * eat time (<= die time) for everyone to survive. 
	also, there are some rules that should be followed:
	- Take 2 forks before eating 
	- State switch in the correct order think -> fork -> fork -> eat n times -> sleep
	- Die if the death timeout is expired
	- No output after death
	- Timestamp in order
	- Only take existing fork
	- Error messages
# 4. How a valid approach should work? 
- a valid approach, should constantly monitor if someone is dead. and if yes, immidiately stop all the threads.
- a valid approach should check for the number of meals ate by philosophers and if the minimum amount provided by the user is ate, start the while program.
- a good approach must not have so much delay. so that philosphers would not die when the number of philos are high.

# 5. My approach:
every philo has a fork. we have an array of fork (mutexes) and their index shows the relevent philosopher. every philo uses her own fork(x) and the left person's fork for eating(x + 1). if there is no left philo after the x's person, the fork for first person will be used, since the philos are sitting around a round table.

- I have a thread, called "the table", that is in parallel to the philosopher routine threads. the point of this thread, is that it is like a 
    table. so every philosopher can see who is eating and who is dead. since it is forbidden by the subject for the philos to talk to each other, 
    and we can not in any sort communicate, the only way for a philosopher for understanding where to finish is to simply look at table. if there is 
    someone dead, then he/she would stop eating. this thread's job is to constantly go over philos and check if they are dead. and when the condition
    of dieing (Tcurrent - Tlast_leat >= Tdie_time) is met, this thread changes the "Death Flag". Also if people ate enough time, this thread, changes 
    the "Enough Meal Flag".        	
- in each phiosopher's thread, there is a while loop that runs forevver if the situation is not stopping it to. so each philosopher eats, and 
    then sleeps and then thinks. but for each act, philosopher first checks the flags. if the Death Flag or the Enough Meals Flag are true, it means 
    that someone is dead or everyone has ate their meals and the philosopher stops from going on. 
- each philosopher has a mutex for the meal variable (last meal's time and number of meals).
- the general data structure (called rules) which is accessible by all the philos had n number of fork mutexes. 
- Eating function:
philo with the philo_id of x calls the eating function. 
there is mutex for fork number x, if the fork is available, the mutex locks it. if not, the mutex waits for it to be available.
whenever it is available, then the mutex for x + 1 fork is locked. (same procedure. only the difference is that if the x == number of philos 
(if the last philo wants to eat) then we will wait for x= 1 fork. so the last person on the table waits for the first person's fork.) 
whenever this fork is free the function will be going on to the next lines of code. 
then there, the philo changes the variables (last meal && number of meals) and spends the time. 
after that, it unlocks the mutexes and comes out. of function. easy.
- Sleeping function:
it only prints and spends time. 
- Thinking function: 
this really does not have to do any thing. just print thinking. because in the philosopher hread there is a while loop that will go to
the eat function and there is the place that philosopher might wait until forks are available, and that waiting time will be considered as thinking.
- To avoid anything from being typed after death announcement:
we have a printing mutex. and whenever sth wants to be printed, we check for thr two flags and if those are safe, we print. 
- To avoid deadlocks:
odd number of philos wait a certain time, then they start. even numbers go eating immidiately. this causes that no two neighbours would
lock a certain fork at the same time. 
- When do we have to use mutexes? 
when we have a shared variable and we want to change it, we lock that variable with mutex. so that everyone trying to change that, should wait until theother one is done. 
- do we have to use a mutex when reading a variable? 
no. when reading, you read the current value of the shared memory. but when changing its value, you need a mutex because otherwise it would be messed up with other values from other people. 
	
  
  to test my approach: 

it goes on a ungoing execution when :
200 470 200 200 (when philosophers are too many, the time lag makes it not possible for philos to survive under 470 ms. although on paper 401 s
should be enough.)
odd number of philos (for example 27 philos) are ongoing with: 630 ms 200 200. 
for some reason, when the sleeping time is too short (60 ms) someone dies. 
: 10 200 100 60 
(I tested some other people's codes and this behaviour happened for all. dont know why yet.)
	
	

