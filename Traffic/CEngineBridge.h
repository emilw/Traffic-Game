//
//  EngineBridge.h
//  Traffic
//
//  Created by Emil Westholm on 2014-03-09.
//  Copyright (c) 2014 Emil Westholm. All rights reserved.
//

#import "EWVehicle.h"

@interface CEngineBridge: NSObject
{
    struct CEngineBridgeImpl* _cEngine;
}

-(NSString*)getValue;
-(EWVehicle*)GetNewVehicle: (EWLane*) lane;
-(EWLane*)SyncLaneWithEngine: (EWLane*) lane;
-(EWVehicle*)UpdatePosition: (EWVehicle*) vehicle deltaTime: (CGFloat) deltaTime;
-(void)UpdatePosition: (NSMutableArray*) vehicles deltaTimes: (CGFloat) deltaTime;

@property NSMutableArray* Vehicles;

@end
