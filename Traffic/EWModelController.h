//
//  EWModelController.h
//  Traffic
//
//  Created by Emil Westholm on 2014-03-04.
//  Copyright (c) 2014 Emil Westholm. All rights reserved.
//

#import <UIKit/UIKit.h>

@class EWDataViewController;
@class EWMainMenuViewController;

@interface EWModelController : NSObject <UIPageViewControllerDataSource>

- (UIViewController *)viewControllerAtIndex:(NSUInteger)index storyboard:(UIStoryboard *)storyboard;
- (NSUInteger)indexOfViewController:(UIViewController *)viewController;

@end
