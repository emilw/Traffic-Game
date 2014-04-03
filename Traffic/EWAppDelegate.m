//
//  EWAppDelegate.m
//  Traffic
//
//  Created by Emil Westholm on 2014-03-04.
//  Copyright (c) 2014 Emil Westholm. All rights reserved.
//

#import "EWAppDelegate.h"

@implementation EWAppDelegate

@synthesize highScore;

-(void)addHighScore:(float)score{
    
    [highScore addObject: [NSNumber numberWithFloat: score]];
    
    [highScore sortUsingSelector: @selector(compare:)];
    
    [highScore writeToFile:scoreListPath atomically:YES];
}

-(NSMutableArray*)getHighScore{
    return highScore;
}

-(void)playBackgroundMusic{
    [musicPlayer play];
}

-(void)stopBackgroundMusic{
    [musicPlayer stop];
    [musicPlayer setCurrentTime:0.0];
}


- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions
{
    // Override point for customization after application launch.
    
    NSArray *paths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
    NSString *documentDirectory = [paths objectAtIndex:0];
    
    scoreListPath = [documentDirectory stringByAppendingPathComponent:@"scores.plist"];
    
    highScore = [NSMutableArray arrayWithContentsOfFile:scoreListPath];
    
    if(highScore == nil)
    {
        highScore = [NSMutableArray array];
    }
    
    
    musicPlayer = [AVAudioPlayer alloc];
    
    NSError* error;
    
    NSString* filePath = [[NSBundle mainBundle] pathForResource:@"MusicTrack" ofType:@"mp3"];
    
    NSURL* url = [NSURL fileURLWithPath:filePath];
    
    //NSURL* musicURL = [NSURL fileURLWithPath:[NSBundle mainBundle] pathForResource:@"MusicTrack.mp3"];
    
    [musicPlayer initWithContentsOfURL:url fileTypeHint:@"mp3" error: &error];
    
    musicPlayer.numberOfLoops = -1;
    
    //if(error)
    
    return YES;
}

- (void)applicationWillResignActive:(UIApplication *)application
{
    // Sent when the application is about to move from active to inactive state. This can occur for certain types of temporary interruptions (such as an incoming phone call or SMS message) or when the user quits the application and it begins the transition to the background state.
    // Use this method to pause ongoing tasks, disable timers, and throttle down OpenGL ES frame rates. Games should use this method to pause the game.
}

- (void)applicationDidEnterBackground:(UIApplication *)application
{
    // Use this method to release shared resources, save user data, invalidate timers, and store enough application state information to restore your application to its current state in case it is terminated later. 
    // If your application supports background execution, this method is called instead of applicationWillTerminate: when the user quits.
}

- (void)applicationWillEnterForeground:(UIApplication *)application
{
    // Called as part of the transition from the background to the inactive state; here you can undo many of the changes made on entering the background.
}

- (void)applicationDidBecomeActive:(UIApplication *)application
{
    // Restart any tasks that were paused (or not yet started) while the application was inactive. If the application was previously in the background, optionally refresh the user interface.
}

- (void)applicationWillTerminate:(UIApplication *)application
{
    // Called when the application is about to terminate. Save data if appropriate. See also applicationDidEnterBackground:.
}

@end
