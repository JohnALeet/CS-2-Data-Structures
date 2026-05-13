# CSCI2
Name: Lab 1 - Game of Life
Date: 02/08/26
Grade: 60/100
Notes: 
It took me awhile to get the progress I have. This was difficult and frustrating. I didn't make the due date. The program forced me to think very hard and reason through the assignment piece-by-piece. I was nearly always having to Google something. You'd mentioned you'd get problems and then put off doing them and let them metabolize in the background, and then the answer would come to you. This was similar to what happened to me. 

The first thing I did was get the file I/O working which didn't seem too difficult. I knew that I needed to set my loops to boardsize to cap my iterations. I'm not sure why int boardSize is allowed/okay in parameters, but it's a size_t type in main. But I trust your judgement.

I worked with tutors to get this far, I'm not sure if I'll be able to get it all done.

I learned a lot, though. It made me think about passing information through parameters & the heap a lot differently, as well as how I might go about using structs in the future. I found the layout of the program's information difficult to track, which I think was the intent. It was fun working with all the different nested loops in the functions, but it was also quite difficult.

As of right now, I am still trying to figure out just how the hell to handle cellState and numNeighbors.

Name: HW1 - Classes Foundations
Date: 02/23/2026
Grade: 90/100

Captain's log: 
This assignment was pretty straight-forward. You did a lot of this in class. I had to look up some file I/O syntax, but nothing here seemed too scary yet.

In my SWClass.h I have a "void" function for fridayCatShirt, I intend to make this a kind of "OP" item at some point. I think maybe I'll add items in
vectors later on. I still haven't gotten my GitHub stuff figured out.

Name: Lab 2 - Point
Star Date: 02/28/2026
Grade: 90/100
Captain's log: 
This lab wasn't that bad at all. Nowhere near as difficult as lab 1. Once I got the for-loop in calcNearestPoint working, it was pretty much done from there. I wrote distPoints first, which helped me to think about the main loop better. My main loop probably could've been written better and cleaner, but she works.

Name HW2
Star Date: 03/20/2026
Grade: 90/100
Captain's log: 
This HW was pretty straight-forward. I used your code for Virtual Animal speaking as a rough skeleton for the layout of my code.
I copied Mersenne Twister from Google. Initially I deleted the Save/Load features because I didn't think they were going to be used going forward. They've been added back. I also added a critical hit RNG to the main combat loop because that seemed kinda cool.

HW3
Star Date: 04/02/2026
Grade: 90/100
Captain's Log:
I added the overloading capabilities to the header file and main. I realize I probably should've had two .cpp files from the start. My main is a bit cluttered.
I know that in the main combat loop, the stats aren't actually being modified, but the operators are still working as intended.

Lab 3
Star Date: 04/05/2026
Grade: ??/100
Captain's Log:
This was actually harder than I thought it'd be. I wrote gcd first, which helped me to write simplify. I had fun with this one. 


Star Date: 05/11/2026
Captain's Log:
I haven't updated the ReadMe much at all. That's my fault. I should've been more on top of that. I feel like taking CS3 and CS2 at the same time was pretty challenging for me. I learned a lot, though. I'm actually surprised how much I learned. I had to study hard, review old lectures and really struggle. As of writing this, I am hammering away at the final, and I imagine you'll see a lot of D2L screenshots be submitted, soon, too.

I went back and looked at Lab 1, which I thought to be exceptionally difficult the first time around. I was able to figure out how to write the updateCellState function to work, and I got the program running. It was a nice feeling to come back to that problem and understand it better. I needed to let it marinate in the background long enough that I could think about it cleaner. As of writing this, it's Monday at 11:30pm on Final's week. I've not slept since Sunday.

This has been the most challenging semester I've ever had. But you were an awesome professor, and you renewed my love and interest in computer science. I loved your interactive teaching style and how humble you came off. I've dealt with professors before who seem to skirt questions or jump head first into jargon when I ask for simple concepts broken down, but you never did that. You seem to operate from the most basic principles of understanding, and it really helps an ape like me follow along.

In regards to my final project, it doesn't look the best, but I'm proud of it. I really had to reason cleanly from the structure of describing objects. Looking back, I think I could've easily merged Character into Combatant, and just make player.h and enemy.h inherit from that. It would've been one fewer .h file in the final. I'd have like to added more rooms and better RNG, but I didn't give myself enough time. I also considered making the combat loop a "typing" game where you have to type out a word quickly, or lose health. That was the working idea, but, well.... time.

Things that went well: reusing my old code. That was actually really cool to use my old SW.h file as a reference for these files. I think it's pretty easy to see the bones of the Star Wars game you had us make earlier in the semester in my final. The linked list also worked really nicely.

Things that didn't go well: reusing my old code. I realized how much of a mess my old SW.h file actually was, so I had to clean that up quite a bit to get it in a cleaner state.



Thank you, Bergen. Have a great trip in China. I hope I run into you again.