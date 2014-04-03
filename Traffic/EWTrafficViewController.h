//
//  EWTrafficViewController.h
//  Traffic
//
//  Created by Emil Westholm on 2014-03-05.
//  Copyright (c) 2014 Emil Westholm. All rights reserved.
//

#import <UIKit/UIKit.h>

#import "EWTrafficController.h"//;
//@class EWTrafficController;

@interface EWTrafficViewController : UIViewController
{
    EWTrafficController* gameController;
    UILabel* _innerRemainingTimeLabel;
    UIView* gameOverView;
}

@property (nonatomic,retain) IBOutlet EWTrafficController* gameController;
@property (nonatomic) IBOutlet UILabel* remainingTimeLabel;
@property (nonatomic) IBOutlet UILabel* totalScoreLabel;
@property (nonatomic) IBOutlet UIView* gameOverView;
@property (nonatomic) IBOutlet UIView* gameIsPausedView;

-(void) setRemainingTime: (float) remainingTime;
-(void) setTotalScore: (float) totalScore;
-(void) displayGameOver;
-(IBAction) pauseGame: (id) sender;


@end
