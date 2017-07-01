# [UNFINISHED] Caber Toss Visualisation

This project is extension of work on my collage subject *Seminar 2*, were he had to model some real life problem, code it, and write paper analysing solutions.
Everything in `./caber` folder is result of that work, missing only main function which simulated caber toss for many starting conditions.
Physics behind caber model is based on the article *Optimizing the Human Dynamics of the Caber Toss* by *Giulia Fanti* and *Michael Hughes* ([see more](https://996ce676-a-62cb3a1a-s-sites.googlegroups.com/site/michaelchughessite/projects/dynamics-of-caber-toss/OptimizingHumanDynamicsOfTheCaberTossWeb.pdf?attachauth=ANoY7crLB0hbBIKprRTZFqZK79Gn9jp2wFjJs9N5Ec-LDm3wZqEt5tQge_JzUeDUvosb7pO-FKCXPmjQKsi_CpmFpjdzrj5rRvk0ASme3aNJGWvbOtJ-EbYsJlRuy8h8haJirPTcEVcJKnxR2RIKrlJg-b0RrW2cKcUGa4IdTzare3Rt3pzwoMddkcmd7jT4CySydaT3R1wRS3-nnABsKneoGIe9x7HI_8UTWJih8bL0f4m4yshyWo6LV7ME2VAW8wOgXNaAX6s9V6MzJYcLwxV_-yS0xcB9febo8x92_ollCVEZUsvyUT0TBVpMAHtXWSyXhKvanZgu&attredirects=0)).

Rest of the project is my try visualise that toss.

### Bulding

Prerequisites:
* *C++11* compiler or later version.
* *OpenGL*.

Once you have prepared everything, just run `make` command from root folder for compiling.

### Running

Just run compiled executable with given settings file given as command line argument.

##### Example
This is example of building and running out of the box. Navigate into the root of the project, before executing following:

~~~~
make
./project settings.conf
~~~~

### Development

This is still unfinished and buggy version. Check TODO secetion to see what is planed to do. Feel free to add suggestions or help with development.

### TODO
This is what I plan to do before declaring project finished.
1. **Fix landing phase**
Since landing phase of simulation messes with coordinates for easier and faster calculation (remember, this was initially only numerical calculation to check which starting conditions result with un/successful toss), it breaks visualisation from the moment caber touches the ground.
2. **Redesign GUI**
    1. Wait *(for user input?)* before restarting simulation
    2. Don't run through all settings every time before starting new simulation. Show all settings on the screen with simulation and offer user to click on what he wants to change.
3. **Redesign reading from .config files**
It is ugly and badly designed with a lot of repeating. Almost impossible to maintain or edit.

### Author
Tomislav Bukić


License
----

This project is under MIT license.
