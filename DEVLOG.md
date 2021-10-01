## 2021-09-26

I have downloaded and installed Unreal Engine. I did this through the [EPIC Launcher](https://www.epicgames.com/store/en-US/download) which I already had installed since Epic gives away free games every week and I collect them just because. Given the size, I downloaded it to my high capacity hard disk. This was a mistake. When I started it up, it ground the hard drive like crazy and took ages to start up. After some quick googling, I found a way to transplant this to my SSD and the startup is much faster.

I've had a few false starts when creating the initial project as there are a ton of options. Eventually, I just ended up creating a "blank" C++ project. From the documentation and youtube videos I've been browsing in the interim, it seems that when you don't know what you are doing, blueprint projects are ideal since it has all the context-sensitive help to guide you along the way. In contrast, the API reference on EPIC's website is no MSDN, and finding things in there is kind of rough. There's also no offline version. However, given my evaluation stipulation was to "Use C++ as much as possible", I elected for the C++ approach anyway. If things get rough, I may create a parallel blueprint project just to guide me along the basic concepts.

A very irritating thing was that the editor seemed to want to activate my Oculus Rift, and when I shut down that service - Steam VR. It did this every time I started it up or ran a project. I finally figured out that disablling the relevant plugins fixed that issue.

## 2021-10-01

It's been 5 days since I first set up this project, and browsed all the learning resources I could find on Unreal Engine. I have not touched it since. This is partly because I have a day job that took up the days in the interim. The other thing is that it gives my subconscious time to absorb what I learned and formulate a plan of action. Given that my deadline is on Oct 4, 4 days should be more than enough to complete a coding test.

The plan of action is that I will create a simple FPS, and use the projectile to trigger the dismount and ragdoll. I will limit the number of bullets (likely to 5), and the goal of the game will be to cause as much damage as possible. The Dismount chracter will ragdoll upon being hit by the first projectile and start racking up damage numbers.

To this end, I have followed the official [FPS Shooter Tutorial](https://docs.unrealengine.com/4.27/en-US/ProgrammingAndScripting/ProgrammingWithCPP/CPPTutorials/FirstPersonShooter/) and I am beginning to get a grasp of the culture of the engine and how it wants to be interacted with. I'm fairly happy with the result as I now have my projectile launcher as well as a rudementary HUD.

I'm a bit dubious about the amount of initialization that's going on inside constructors. Still, that's how the tutorial was structured, and therefore what EPIC recommends. There's probably better practices in the way to set things up, but right now my focus isn't on being perfect but simply learning. The next stage is where the training wheels come off and I start digging deeper.
