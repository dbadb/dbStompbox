# dbStompbox

dbStompbox is a simple TeensyLC-based MIDI controller.

Stompboxes are useful for hands-free music-making. Combine a stompbox
with a looper and a guitar and magic musical moments (TM) are are
yours for the picking.

dbStompbox was built as part of a tutorial of Fiddle's Looper capability.
Fiddle is a free and open music-making engine (DAW).  You can learn more
about Fiddle [here](https://cannerycoders.com/#Fiddle).

<center>
<img src="./images/overview.png">
</center>

## The Prerequisites

* Familiarity with Arduino Development
* Handy with a Soldering Iron
* Musically Inclined

## The Hardware Design

It's amazingly simple to build your own custom MIDI controller.  Combine
any number of digital sensors with a Teensy and you are on your way. 

In this example, we support two expression pedals (for, eg Wah and Volume) 
with a number of foot-switches (for, eg multi-channel looper control)
to deliver hands-free control over a DAW for guitar players.

We house the Teensy and phone-socket connection points in a free-standing
cigar-box.  The sturdy wooden construction of these boxes make it easy to 
mount hardware connection points.

As a separate "device", we house the 6 footswitches.  Each switch is
connected to the  USB box through its own phone jack and this allows us
to support off-the shelf MIDI sustain pedals in addition to our custom 
footboard.

| Part          | Count | Description              | Link                                              | Approximate Cost |
| :------------ | :---- | :----------------------- | :------------------------------------------------ | :--------------- |
| Teensy LC     | 1     | Microcontroller          | [pjrc](https://www.pjrc.com/teensy/teensyLC.html) | $15              |
| M-Audio EX-P  | 2     | Expression Pedal         | [Amazon](https://www.amazon.com/dp/B000NLRWEI)    | $30 ea           |
| TRS Sockets   | 2     | For expression pedals    | [Amazon](https://www.amazon.com/dp/B079K74SC4)    | $2.50 ea         |
| Phone Sockets | 6     | For external stopbox     | [Amazon](https://www.amazon.com/dp/B07FB944VD)    | $.75 ea          |
| Phone Jacks   | 6     | From footboard to Teensy | [Amazon](https://www.amazon.com/dp/B07JP82FFX)    | $1 ea            |
| Foot Switches | 6     | Momentary Foot Switches  | [Amazon](https://www.amazon.com/dp/B08TBTWDYV)    | $2 ea            |
| Footboard     | 1     | A piece of wood          |                                                   | $0 - $20            |
| Wire, Solder  |  | | | |

Total cost without expression pedals is under $30 dollars. A bargain at twice
the price.

## Wiring

The Teensy wiring is trivial.  Each footswitch is a button operating in
pullup mode. This means that one button terminal is connected to ground
an the other to a digital pin.  Here pins D0-D5 are connected to your buttons.

<center>
<img src="./images/teensyPins.png">
</center>

Pins A8, A9 are used to sample the expression pedals.  Expression pedals
introduce a variable resister (potentiometer) between the reference voltage
and ground.  In the 3.3V TeensyLC, the reference signal is obtained from either
ARef or the 3.3V pin.  Here is a crude diagram represeting the portion of
the TRS jack and the associated signal.

<center>
<img src="./images/trsWiring.png">
</center>

## To Build the Software

Load the `.ino` file into the [Teensyduino](https://www.pjrc.com/teensy/td_download.html) 
software.

Make sure to select Teensy LC as your board.

Select Serial+Midi as the USB Type.

Build and deploy.

## Photos

Here's the cigar box to house the TeensyLC:

<img src="./images/dbCigarbox.jpg" style="width:50%">

Here's the Teensy wired and in place:

<img src="./images/dbStompBox.jpg" style="width:50%">

And now it's ready for action:

<img src="./images/dbStompBoxClose.jpg" style="width:500px">

Here's the footboard:

<img src="./images/dbStompBoard.jpg" style="width:500px">

And the whole setup, complete with expression pedals:

<img src="./images/dbStompAction.jpg" style="width:500px">
