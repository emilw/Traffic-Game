//
//  EWMainMenuViewController.h
//  Traffic
//
//  Created by Emil Westholm on 2014-03-05.
//  Copyright (c) 2014 Emil Westholm. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <QuartzCore/QuartzCore.h>
#import "CEngineBridge.h"

@interface EWMainMenuViewController : UIViewController
{
    IBOutlet UIButton* startNewGameButton;
    IBOutlet UIButton* statsButton;
    IBOutlet UIButton* settingsButton;
    
    CAKeyframeAnimation* popAnimation;
}

//@property UIButton newGameButton;
@property (strong,nonatomic) IBOutlet UIButton *startNewGameButton;
@property (strong,nonatomic) IBOutlet UIButton *statsButton;
@property (strong,nonatomic) IBOutlet UIButton *settingsButton;
@property (strong, nonatomic) IBOutlet UILabel *dataLabel;

-(IBAction) newGame:(id)sender;
-(IBAction) showState:(id)sender;
-(IBAction) showSettings:(id)sender;

@end
