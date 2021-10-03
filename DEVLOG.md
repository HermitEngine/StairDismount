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

## 2021-10-03 (Post-mortem)

This project was quite a good introduction to UE4 and the way it operates. I got a good sense of the way things are done, and am reasonably confident of learning and adapting any other functionality that I might need in the future. Here are some key highlights.

### Blueprints

Blueprints are a very impressive tool. While flow-charting is just as clunky as it was from the days of Virtools, I can see that it is a good way to offload tweaking to designers. For programmers, however, the real value is in the exposure of variables.

Const variables and similar macros should be a thing of the past. If you have one, simply make it a property and expose it to the editor. The only place I felt compelled to add a constexpr was in the GameHUD class, mainly because it was badly structured. Like every other class, it should have had a derived blueprint. The parameter components that are hardcoded in the constructor should be set via the editor. It was implemented the way it was simply because I was following along the tutorial and didn't know any better. It is unlikely I'll write code in that style in the future. Nevertheless, it's still neat that you can reference any asset by lookup. However, if you rename, delete or move the asset, the editor simply crashes.

Other things I should have exposed to the editor are some of the numbers used for the Bullet. Most notably, the multiplier for how much impulse to forward to the colliding objects, and the threshold for determining if a CrashDummy collision is score-worthy. Note that these are number literals rather than const-like expressions. This is style I've had for a long time because it makes the code much easier to read and tweak if you don't have to keep jumping around the code to find its definition. The rule I follow is that if an expression is only used once the code, it is a literal. More than that, and it gets a const because the trade-off for convenient tweaking is worthwhile, and at this point, its value means something significant to the whole codebase that can now be relayed though the const's name.

All that being said, I have no idea what the runtime cost of exposing these numbers to blueprints are. The current project is far to small to produce a meaningful profile, and in any case, that's probably beyond the current scope. However, in the back of my mind, I'm mentally prepared that we might have to go through and convert all these blueprints back to consts once the final values are agreed upon, or simply live with the cost. There has to be a reason why Unreal games and apps in general have a slower loading time and consume more battery power than other engines including Unity3D. Could be the richness of its features, or could be this.

### Documentation

Documentation for UE4 is generally good. The video tutorials were excruciatingly slow and it was hard to get value out of them. The text ones, however, were golden. Having been around for a long time, there's of course a great deal of community content, tutorials, and [Stack Overflow](https://stackoverflow.com) questions.

The one thing I wish was available was an offline API reference. I suppose one could send a spider to scrape the website, but given the huge disk footprint of the engine, you'd expect that to be bundled.

### Marketplace and Assets

The Marketplace is a great place for placeholder and example assets. Unfortunately, because we picked the latest version: 4.27 of the engine, a lot of them weren't updated to be compatible with it yet, placing them out of reach. When I was looking for the mannequin model, an online resource said that you could just grab it from the marketplace. Unfortunately, it was one of those that wasn't quite compatible. What I had to do was create a seperate temporary 3rd-person project, and migrate it from there to the StairDismount one. Not the most elegant solution, but it worked!

Importing raw assets like fbx files, sounds, bitmaps, etc. was as easy as drag, drop and forget. The editor is kind enough to offer to create default interfaces (like materials and font faces) for these raw assets so there's at least something to modify or copy.

### Code Structure

The way the code is structured by default is reasonable. Every class seems to have its place and purpose. The generated code was far too verbose in its comments, but that seems reasonable given that it would be an introduction for all levels of programmers. I ended up removing all the comments, because the code that needed to be written was straight-forward enough that an English description would be no better than the C++ one.

This project, in general, was simple enough that it didn't require any architecting. I just followed the default flow. That being said, this would generally be my approach at a first run-through of new tech regardless.

- First Run: Implement everything as prescribed, whether you agree with it or not. Just to get the idea of what the engine is trying to do and what it expects from the programmer.
- Second Run: Make changes based on past experience to suit the context of the project. At this stage, I'm likely to overcompensate and cause unintended side-effects
- Third Run: By this time, I become pretty aware of the pitfalls and hacks, and can make subtler tweaks for greater effect. At this stage, I'm comfortable.
- Seventh Run: It usually takes around this number of runs to truly claim mastery over any non-trivial tech.

### Potential Future Features

If this project were to become a full-fledged game. The first thing I would add is persistent high score. This gives the player an instant goal, and increases addictivity by about 247%. Bonus points if it's online so that you can compete against the world or your social network. (Somebody will hack it to get maximum score though)

The second thing is more interesting level design. In the case of our current level, I heavily neutered the bullet so that it doesn't produce much impulse. This makes optimal way to get a high score methodically nudging the character so it rolls down the steps. However, by increasing the bullet potency, you can literally make the character fly all over the place, and with some tweaks to gravity, perhaps introduce some juggling mechanics. Given that the mannequin, has a full skeletal mesh, it could also be playing some sort of dance animation so timing the first hit becomes a factor. The possibilities are out there.

The last thing would simply be polish. A prettier UI (though the current text-based one has a certin rustic appeal). Perhaps renaming the game to some pun off six-shooter. More sounds, especially on dummy-environment collisions, and a little background music.

### Epilogue

All that said, the key thing about any project is knowing when to stop. I came into this knowing that as a first run it will be throw-away code, and in its current state it has served its purpose. I now feel somewhat at home in the Unreal environment, and am confident I could recreate this project in a third of the time if required. It also serves as an indicator of what I can do with a reasonably good but complex engine that I am entirely new to in 12 hours. It's been fun, and thanks for following along on this journey!
