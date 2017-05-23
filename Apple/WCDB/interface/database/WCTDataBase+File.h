/*
 * Tencent is pleased to support the open source community by making
 * WCDB available.
 *
 * Copyright (C) 2017 THL A29 Limited, a Tencent company.
 * All rights reserved.
 *
 * Licensed under the BSD 3-Clause License (the "License"); you may not use
 * this file except in compliance with the License. You may obtain a copy of
 * the License at
 *
 *       https://opensource.org/licenses/BSD-3-Clause
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#import <Foundation/Foundation.h>
#import <WCDB/WCTDataBase.h>

/**
 This category contains file operation interface for database.
 Since database is a binary file, there is a risk of file operations, which may lead to corrupted database or data loss.
 */
@interface WCTDataBase(File)

/**
 Remove all database-related files.
 You should call it on a closed database. Otherwise you will get a warning.

 @param error error
 @return YES if all files are removed.
 */
- (BOOL)removeFilesWithError:(WCTError**)error;

/**
 Move all database-related files and some extra files to directory safely.
 You should call it on a closed database. Otherwise you will get a warning and you may get a corrupted database.
 
 Since file operation is not atomic, There may be some accidents during this period.
 For example:
    App may crash while db file is moved to destination and wal file is not. 
    Then none of destination and source contains the whole data.
 This interface can make sure all of your data is in source or destination. 

 @param directory destination
 @param extraFiles extraFiles
 @param error error
 @return YES if all files are moved.
 */
- (BOOL)moveFilesToDirectory:(NSString*)directory withExtraFiles:(NSArray<NSString*>*)extraFiles andError:(WCTError**)error;

/**
 This interface is equivalent to [database moveFilesToDirectory:directory withExtraFiles:nil andError:error].

 @param directory destination
 @param error error
 @return YES if all files are moved.
 */
- (BOOL)moveFilesToDirectory:(NSString*)directory withError:(WCTError**)error;

/**
 Paths to all database-related files.

 @return paths
 */
- (NSArray<NSString*>*)getPaths;

/**
 Get the space used by the database files.
 You should call it on a closed database. Otherwise you will get a warning.

 @param error error
 @return The sum of files size in bytes.
 */
- (NSUInteger)getFilesSizeWithError:(WCTError**)error;

@end
