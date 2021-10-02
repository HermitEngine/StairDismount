## 2021-09-26 (1 hour)

I have downloaded and installed Unreal Engine. I did this through the [EPIC Launcher](https://www.epicgames.com/store/en-US/download) which I already had installed since Epic gives away free games every week and I collect them just because. Given the size, I downloaded it to my high capacity hard disk. This was a mistake. When I started it up, it ground the hard drive like crazy and took ages to start up. After some quick googling, I found a way to transplant this to my SSD and the startup is much faster.

I've had a few false starts when creating the initial project as there are a ton of options. Eventually, I just ended up creating a "blank" C++ project. From the documentation and youtube videos I've been browsing in the interim, it seems that when you don't know what you are doing, blueprint projects are ideal since it has all the context-sensitive help to guide you along the way. In contrast, the API reference on EPIC's website is no MSDN, and finding things in there is kind of rough. There's also no offline version. However, given my evaluation stipulation was to "Use C++ as much as possible", I elected for the C++ approach anyway. If things get rough, I may create a parallel blueprint project just to guide me along the basic concepts.

A very irritating thing was that the editor seemed to want to activate my Oculus Rift, and when I shut down that service - Steam VR. It did this every time I started it up or ran a project. I finally figured out that disablling the relevant plugins fixed that issue.

## 2021-10-01 (3 hours)

It's been 5 days since I first set up this project, and browsed all the learning resources I could find on Unreal Engine. I have not touched it since. This is partly because I have a day job that took up the days in the interim. The other thing is that it gives my subconscious time to absorb what I learned and formulate a plan of action. Given that my deadline is on Oct 4, 4 days should be more than enough to complete a coding test.

The plan of action is that I will create a simple FPS, and use the projectile to trigger the dismount and ragdoll. I will limit the number of bullets (likely to 5), and the goal of the game will be to cause as much damage as possible. The Dismount chracter will ragdoll upon being hit by the first projectile and start racking up damage numbers.

To this end, I have followed the official [FPS Shooter Tutorial](https://docs.unrealengine.com/4.27/en-US/ProgrammingAndScripting/ProgrammingWithCPP/CPPTutorials/FirstPersonShooter/) and I am beginning to get a grasp of the culture of the engine and how it wants to be interacted with. I'm fairly happy with the result as I now have my projectile launcher as well as a rudementary HUD.

I'm a bit dubious about the amount of initialization that's going on inside constructors. Still, that's how the tutorial was structured, and therefore what EPIC recommends. There's probably better practices in the way to set things up, but right now my focus isn't on being perfect but simply learning. The next stage is where the training wheels come off and I start digging deeper.


## 2021-10-02 (3 hours)

Today was all about collisions and responses, and I'm satisfied that I have the basic of what's required for the actual test evaluation. The bullet I coded yesterday now collides with my shiny new mannequin. On first collision, the mannequin will ragdoll, and every time it collides with something or other, I get a number based on the velocity differential to add to a score.

The bulk of frustration today was figuring out how the collisions actually work since apparantly for skeletal actors, the way you do it is totally different from the way our bullet was handled in the nice tutorial. Also sad was that in the collision response function, they provided an Impulse vector, but that was always zero. Known bug apparently. All in all, this is not that much of a C++ test given that very little code is actually written. It's more of a figure-out-what-the-engine-wants-you-to-do test.

On hindsight, I'd fully expect a competent Unreal Engine developer would be able to finish this in a few hours. A pretty reasonable assignment for a code test. My problem is that I'm groping around like a blind man... I suppose everybody starts somewhere!

All that's left now is to hook up the score and bullet count to the HUD. Some general level design to make things pretty. And a little game state management to restart or end the simulation after all bullets are expended. I feel like the hard part is over, but I could be wrong!

## 2021-10-03 (5 hours)

I didn't intend to finish this project in the wee hours of the morning, but I had an hour or so before bed time, so I thought I'd shove in some HUD work to kill the time. One thing led to another and it's now 5am and I have a working HUD, sounds, gameplay, level design, bullet counting, audio and level resetting.

The HUD itself was fairly easy. Just needed to find a font and print out some text. Getting things to talk to the HUD was another thing. I ended up letting GameModeBase house the variables since it's easily accessible and have everybody dig into it from there. Not sure if this is the right approach.

The rest of the minor functionality like bullet counting and level resetting took almost no time at all. The first being common sense, and the latter merely being a matter of googling the appropriate command. It's a pity that I found out about the UGameplayStatics at such a late stage as it looks like there are many goodies in there.

The bulk of the time was spent on level building and tweaking the projectile strength and efficiency. I decided not to spend even more time perusing the asset store, but just made everything out of cubes in true programmer art style. Though I initially intended not to include sound, it felt like I had to simply because it was lacking that bit of character. Adding them in was simple enough, but finding the right sounds was a little time consuming.

I'm going to go to bed now, but when I wake up, I'll do a little post-mortem and call it a wrap!