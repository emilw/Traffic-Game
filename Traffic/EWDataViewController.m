//
//  EWDataViewController.m
//  Traffic
//
//  Created by Emil Westholm on 2014-03-04.
//  Copyright (c) 2014 Emil Westholm. All rights reserved.
//

#import "EWDataViewController.h"

@interface EWDataViewController ()

@end

@implementation EWDataViewController

- (void)viewDidLoad
{
    [super viewDidLoad];
	// Do any additional setup after loading the view, typically from a nib.
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (void)viewWillAppear:(BOOL)animated
{
    [super viewWillAppear:animated];
    self.dataLabel.text = [self.dataObject description];
    
    //self.dataLabel.text = @"testing";
}

@end
