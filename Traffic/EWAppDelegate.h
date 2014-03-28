//
//  EWAppDelegate.h
//  Traffic
//
//  Created by Emil Westholm on 2014-03-04.
//  Copyright (c) 2014 Emil Westholm. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <AVFoundation/AVFoundation.h>
@interface EWAppDelegate : UIResponder <UIApplicationDelegate>
{
    NSMutableArray* highScore;
    NSString* scoreListPath;
    AVAudioPlayer* musicPlayer;
}

@property (strong, nonatomic) UIWindow *window;
@property (nonatomic, retain) NSMutableArray* highScore;

-(void)addHighScore:(float) score;
-(NSMutableArray*)getHighScore;
-(void)playBackgroundMusic;
-(void)stopBackgroundMusic;

@end
