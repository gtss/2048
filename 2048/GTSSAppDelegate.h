//
//  GTSSAppDelegate.h
//  2048
//
//  Created by yourname on 14-3-23.
//  Copyright (c) 2014年 gtss. All rights reserved.
//

#import <Cocoa/Cocoa.h>

@interface GTSSAppDelegate : NSObject <NSApplicationDelegate>

@property (assign) IBOutlet NSWindow *window;

@property (readonly, strong, nonatomic) NSPersistentStoreCoordinator *persistentStoreCoordinator;
@property (readonly, strong, nonatomic) NSManagedObjectModel *managedObjectModel;
@property (readonly, strong, nonatomic) NSManagedObjectContext *managedObjectContext;

- (IBAction)saveAction:(id)sender;

@end
