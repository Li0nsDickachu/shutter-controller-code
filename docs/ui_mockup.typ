#show link: underline

= main menu<main>
#image("graphics/home.svg", width: 80%)

#table(
   columns: (40%, 40%),
   align: center,
   stroke: none,
   [Left button:],
   [Right button:],
   [Start],
   [Increment profile 0-9, and circle]
)

#table(
   columns: (80%),
   align: center,
   stroke: none,
   [Both buttons:],
   [Open #link(label("setup"), "profile setup")]
)

= Profile setup<setup>
#image("graphics/setup.svg", width: 80%)

#table(
   columns: (40%, 40%),
   align: center,
   stroke: none,
   [Left button:],
   [Right button:],
   [Edit #link(label("setting"), "setting")],
   [Cycle settings, until last setting is reached, then return to the #link(label("main"), "main menu")]
)

#table(
   columns: (80%),
   align: center,
   stroke: none,
   [Both buttons:],
   [Return to the #link(label("main"), "main menu")]
)
Letters shown: EX, represents scrolling text saying Exposure time
Settings list is as follows:
1. Exposure time
  + default: 0.01 seconds
  + range: 0.01 seconds - 9 hours 50 minutes (increments: .01, .02, ... .1ᵒ, .2ᵒ ... 1, 2 ... 66, 1h1ᵒ, 1h2ᵒ, 1h3ᵒ ... 9h5ᵒ)
+ Delay before first picture
  + default: 0
  + range: 0 seconds - 9 hours 50 minutes (increments: 0, 1, 2 ... 66, 1h1ᵒ, 1h2ᵒ, 1h3ᵒ ... 9h5ᵒ)
+ Amount of pictures
  + default: 1
  + range: ∞, 1 - 999 (∞ acts as -1 in the ui)
+ Repeat delay
  + default: 1 second
  + range: 0.01 seconds - 9 hours 50 minutes (increments: 0, .1ᵒ, .2ᵒ ... 1, 2 ... 66, 1h1ᵒ, 1h2ᵒ, 1h3ᵒ ... 9h5ᵒ)
+ Brightness during exposure
  + default: 10
  + range: 0 - 100
+ Master brightness 
  + default: 100 (affects all profiles and the main menu)
  + range: 1 - 100
+ Focus time before taking picture
  + range: 0.01 seconds - 9 hours 50 minutes (increments: 0, .1ᵒ, .2ᵒ ... 1, 2 ... 66, 1h1ᵒ, 1h2ᵒ, 1h3ᵒ ... 9h5ᵒ)

= Edit setting <setting>
== Integer
#image("graphics/int_inf.svg", width: 80%)
#image("graphics/int1.svg", width: 80%)
#image("graphics/int2.svg", width: 80%)
#image("graphics/int10.svg", width: 80%)
#image("graphics/int100.svg", width: 80%)
#image("graphics/int169.svg", width: 80%)
#image("graphics/int550.svg", width: 80%)
== Time
#image("graphics/time.09.svg", width: 80%)
#image("graphics/time9m30.svg", width: 80%)
#image("graphics/time24m.svg", width: 80%)
#image("graphics/time9h30m.svg", width: 80%)

