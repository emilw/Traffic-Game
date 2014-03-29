//
//  EWVehicle.m
//  Traffic
//
//  Created by Emil Westholm on 2014-03-06.
//  Copyright (c) 2014 Emil Westholm. All rights reserved.
//

#import "EWVehicle.h"
#import "EWTrafficController.h"

@implementation EWVehicle

@synthesize speed, slowed, goalLane, controller, Id;
/*- (id)initWithFrame:(CGRect)frame
{
    UIImage* loadedImage = [UIImage imageNamed: @"RedCar.png"];
    
    CGRect rect = CGRectMake(frame.origin.x, frame.origin.y, loadedImage.size.width, loadedImage.size.height);
    
    self = [super initWithFrame:rect];
    if (self) {
        self.opaque = NO;
        self.backgroundColor = [UIColor clearColor];
    }
    image = loadedImage;
    return self;
}*/


- (id)initWithName:(NSString*)name id:(int)instanceId
{
    UIImage* loadedImage = [UIImage imageNamed: name];
    
    //carType = name;
    
    CGRect rect = CGRectMake(0, 0, loadedImage.size.width, loadedImage.size.height);
    
    self = [super initWithFrame:rect];
    if (self) {
        // Initialization code
        //        image = [loadedImage retain];
        self.opaque = NO;
        self.backgroundColor = [UIColor clearColor];
    }
    image = loadedImage;
    speed = 100;//125;
    self.opaque = NO;
    self.backgroundColor = [UIColor clearColor];
    
    Id = instanceId;
    
    return self;
}


-(BOOL)correctLane {
    //NSInteger tag = self.goalLane.tag;
    
    /*if(tag == 0 && ([carType compare: @"BlueCar"]))
        return YES;
    else if(tag == 1 &&([carType compare:@"RedCar" ]))
        return YES;
    else if(tag == 2 && ([carType compare: @"GreenCar"]))
        return YES;*/
    
    if(self.goalLane.tag == self.goalTag)
        return YES;
    
    
    //NSLog(@"FALSE");
    return NO;
    
}

-(BOOL)outsideOfLane {
    
    CGFloat vehicle = self.center.y;
    
    CGFloat lane = -10.0;//self.goalLane.frame.size.height;//self.goalLane.center.y + self.goalLane.frame.size.height;
    
    //NSLog(@"Vehicle and Lane: %g, %g", vehicle, lane);
    
    if(vehicle < lane)
        return YES;
    
    return NO;
    
}


// Only override drawRect: if you perform custom drawing.
// An empty implementation adversely affects performance during animation.
- (void)drawRect:(CGRect)rect
{
    // Drawing code
    [image drawInRect:rect];
}

/*-(void)touchesEnded:(NSSet *)touches withEvent:(UIEvent *)event{
    UITouch* touch = [touches anyObject];
    self.center = [touch locationInView:[self superview]];
}*/

/*-(void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event{
    UITouch* touch = [touches anyObject];
    self.center = [touch locationInView:[self superview]];
}*/

-(void)touchesMoved:(NSSet *)touches withEvent:(UIEvent *)event{
    UITouch* touch = [touches anyObject];
    //self.center = [touch locationInView:[self superview]];
    [controller vehicleMoved: self];
    
    EWLane* lane = [controller laneAtPoint:[touch locationInView:self.superview]];
    
    if(lane) {
        self.goalLane = lane;
        
        NSLog(@"In a lane");
    }
}

/*-(void)dealloc{
    [image release];
    [super dealloc];
}*/


@end
