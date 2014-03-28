//
//  EWMainMenuViewController.m
//  Traffic
//
//  Created by Emil Westholm on 2014-03-05.
//  Copyright (c) 2014 Emil Westholm. All rights reserved.
//

#import "EWMainMenuViewController.h"
#import "EWTrafficViewController.h"

@implementation EWMainMenuViewController

@synthesize startNewGameButton, statsButton, settingsButton;

-(void)navigateTo:(NSString*) controllerName
{
    UIViewController *toController = (UIViewController*)[self.storyboard instantiateViewControllerWithIdentifier:controllerName];
    [self presentViewController:toController animated:NO completion:nil];
}

-(IBAction)newGame:(id)sender
{
    //self.dataLabel.text = @"new game clicked";
    
    //EWTrafficViewController *myVC = (EWTrafficViewController *)[self.storyboard instantiateViewControllerWithIdentifier:@"EWTrafficViewController"];
    //[self presentViewController:myVC animated:NO completion:nil];
    
    [self navigateTo: @"EWTrafficViewController"];
}

-(void)popView: (UIView*)view{
    [view setHidden:NO];
    [[view layer] addAnimation:popAnimation forKey:@"transform.scale"];
}

-(void)viewWillAppear:(BOOL)animated{
    [popAnimation setDuration:0.3];
    [startNewGameButton setHidden:YES];
    [settingsButton setHidden:YES];
    [statsButton setHidden:YES];
    [self performSelector:@selector(popView:) withObject:startNewGameButton afterDelay:0.25];
    [self performSelector:@selector(popView:) withObject:statsButton afterDelay:0.3];
    [self performSelector:@selector(popView:) withObject:settingsButton afterDelay:0.35];

}

-(IBAction)showState:(id)sender
{
    [self navigateTo: @"EWHighScore"];
}

-(IBAction)showSettings:(id)sender
{
    
}

- (id)init
{
    //index = 0;
    self = [super init];
    return self;
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

    CEngineBridge* bridge = [CEngineBridge new];
    
    NSString* value = [bridge getValue];
    
    self.dataLabel.text = [bridge getValue];
    //self.dataLabel.text = @"Ready";

    
    popAnimation = [CAKeyframeAnimation animationWithKeyPath:@"transform.scale"];
    popAnimation.keyTimes = [NSArray arrayWithObjects:[NSNumber numberWithFloat:0.0], [NSNumber numberWithFloat:0.7],
                             [NSNumber numberWithFloat:1.0], nil];
    popAnimation.values = [NSArray arrayWithObjects:[NSNumber numberWithFloat:0.01],
                                              [NSNumber numberWithFloat:1.1],
                           [NSNumber numberWithFloat:1.0], nil];
    
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

@end
