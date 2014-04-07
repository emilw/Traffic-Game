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

@synthesize controller, Id;

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

// Only override drawRect: if you perform custom drawing.
// An empty implementation adversely affects performance during animation.
- (void)drawRect:(CGRect)rect
{
    // Drawing code
    [image drawInRect:rect];
}

//Only keep these for remembering the other events
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
    NSLog(@"Vehicle %d moved", self.Id);
    
    [controller vehicleMoved: self point:[touch locationInView:self.superview]];
}

@end
