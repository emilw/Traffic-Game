//
//  EWTrafficViewController.m
//  Traffic
//
//  Created by Emil Westholm on 2014-03-05.
//  Copyright (c) 2014 Emil Westholm. All rights reserved.
//

#import "EWTrafficViewController.h"
#import "EWVehicle.h"

@interface EWTrafficViewController ()

@end

@implementation EWTrafficViewController

@synthesize gameController, remainingTimeLabel = _innerRemainingTimeLabel, gameOverView, gameIsPausedView;

-(IBAction) pauseGame:(id)sender{
    NSLog(@"Game is paused");
    [gameController togglePause];
    
    if([gameController isPaused]){
        [self.view addSubview:gameIsPausedView];
    }
    else
    {
        [gameIsPausedView removeFromSuperview];
    }
    
}

-(void) navigateTo: (NSString*) controllerName
{
    UIViewController *toController = (UIViewController*)[self.storyboard instantiateViewControllerWithIdentifier:controllerName];
    [self presentViewController:toController animated:NO completion:nil];

}

-(void) setRemainingTime: (float) remainingTime
{
    NSString* remainingTimeString = [NSString stringWithFormat:@"%1.2f", remainingTime];
    _innerRemainingTimeLabel.text = remainingTimeString;
}

-(void) setTotalScore:(float)totalScore
{
    NSString* totalScoreString = [NSString stringWithFormat:@"Your score: %1.2f", totalScore];
    _totalScoreLabel.text = totalScoreString;
}

-(void) displayGameOver
{
    [self.view addSubview:gameOverView];
    
    [self performSelector: @selector(endGame:) withObject:nil afterDelay:1.5];
}
-(IBAction) endGame: (id)sender
{
    [self navigateTo:@"EWMainMenuViewController"];
}

- (void) viewWillAppear:(BOOL)animated{
    [gameController startGame];
}

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        // Custom initialization
    }
    return self;
}

- (void)viewDidLoad
{
    [super viewDidLoad];
	// Do any additional setup after loading the view.
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

@end
