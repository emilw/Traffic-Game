//
//  EWVehicle.h
//  Traffic
//
//  Created by Emil Westholm on 2014-03-06.
//  Copyright (c) 2014 Emil Westholm. All rights reserved.
//

#import <UIKit/UIKit.h>
@class EWTrafficController;
@class EWLane;

@interface EWVehicle : UIView
{
    UIImage* image;
    EWTrafficController* controller;
    CGFloat speed;
    BOOL slowed;
    NSInteger goalTag;
    int Id;
    BOOL ToBeRemoved;
    
    EWLane* goalLane;
}

-(id)initWithName: (NSString*) name id: (int) instanceId;

@property (nonatomic, retain) EWTrafficController* controller;

@property(nonatomic) int Id;

@end
