/**
* Tag.cpp source file for Tag.h
* CSC3022F Assignment 1 2021
* Author: WNGJIA001
*/

#include <iostream>
#include <fstream>
#include <stack>
#include <string>
#include <vector>
#include "Tags.h"

namespace WNGJIA001{
    std::vector<TagStruct> TagVector;

    void readTagsFrom(std::string fn){
        // read tags from the passed file
        // check validity of the file name
        int fn_length = fn.size();
        if (fn_length < 5) { // minimum requirement is 5 characters e.g. a.txt
            std::cerr << "Invalid file name!" << std::endl;
            return;
        } else if (fn.find('.') != std::string::npos) {
            std::string fextension = fn.substr(fn.find('.')+1);
            if (fextension != "txt") {
                std::cerr << "Invalid file name!" << std::endl;
                return;
            }
        } else { // length > 4 but no extension 
            std::cerr << "Invalid file name!" << std::endl;
            return;
        }
        // open file
        std::ifstream inputFile(fn);
        if (!inputFile){
            std::cerr << "File does not exist!" << std::endl;
            return;
        }
        std::string line;
        std::string content;
        while (std::getline(inputFile, line)) {
            // read all lines into string content
            content = content + line;
        }  
        // close file
        inputFile.close();   

        // firstly removes all elements from the vector before reading from new file 
        TagVector.clear(); 
        // then extract tags and texts from content and add to TagVector
        std::string tag_name;
        std::string tag_text;
        std::stack<std::string> nameStack;
        std::stack<std::string> textStack;
        do { // repeat this process until content is empty
            tag_name = getTagName(content); // read next tag in content
            content = getContentAfterTag(content); // read content after the first tag
            tag_text = getTextAfterTag(content); // read text before the next tag
            nameStack.push(tag_name);
            textStack.push(tag_text);
            do { // repeat this process until stacks empty
                tag_name = getTagName(content);
                if (tag_name == ("/"+nameStack.top())) { 
                    // if next tag is a closing tag for namestack.top()
                    std::string tag_n = nameStack.top();
                    std::string tag_t = textStack.top();
                    // remove the top elements from namestack and textstack and add the tag to vector
                    nameStack.pop();
                    textStack.pop();
                    addTag(tag_n, tag_t);
                    content = getContentAfterTag(content);
                    tag_text = getTextAfterTag(content);
                    if (!tag_text.empty()) {
                        tag_t = textStack.top() + tag_text;
                        textStack.pop();
                        textStack.push(tag_t);
                    }
                } else {
                    content = getContentAfterTag(content);
                    tag_text = getTextAfterTag(content);
                    nameStack.push(tag_name);
                    textStack.push(tag_text);
                }
            } while (!nameStack.empty());
        } while (!content.empty());
    }

    void printTags() {
        // print data of all the TagStructs within TagVector to console output
        if (TagVector.empty()) { // if empty vector, no tags to print
            std::cout << "No tags to print, select \"r\" in menu to start reading tags from a text file!" << std::endl;
        }
        else { // else: vector contains element
            for(auto tagIt = TagVector.begin(); tagIt != TagVector.end(); tagIt++ ) {
                // iterate through vector to print out data of each element/TagStruct
                std::cout << "\"" << (*tagIt).name << "\"";
                std::cout << "," << (*tagIt).quantity << ",";
                std::cout << "\"" << (*tagIt).text << "\"" << std::endl;
            }
        }
    }

    void dumpTags() {
        // write data of all the TagStructs within TagVector to bin/tag.txt
        if (TagVector.empty()) { // if empty vector, no tags to export
            std::cout << "No tags to export, select \"r\" in menu to start reading tags from a text file!" << std::endl;
        }
        else { // else: vector contains element
            std::ofstream outputFile("bin/tag.txt");
            for(auto tagIt = TagVector.begin(); tagIt != TagVector.end(); tagIt++ ) {
                // iterate through vector to export data of each element/TagStruct to outputFile
                outputFile << "\"" << (*tagIt).name << "\"";
                outputFile << "," << (*tagIt).quantity << ",";
                outputFile << "\"" << (*tagIt).text << "\"\n";
            }
            // close file
            outputFile.close();
            std::cout << "Tags have been exported to bin/tag.txt" << std::endl;
        }
    }

    void listTag(std::string tn) {
        // list the data of the tag if a TagStruct with the passed tag name is present in TagVector
        std::string tagName = tn;
        auto tagIt = std::find_if(TagVector.begin(), TagVector.end(), [&tagName](TagStruct& ts) { return ts.name == tagName; } );
        if (tagIt != TagVector.end()) { // found a TagStruct with the Tag name
            std::cout << "Tag name: " << (*tagIt).name << std::endl;
            std::cout << "Number of occurrence(s) of the tag: " << (*tagIt).quantity << std::endl;
            std::cout << "Text enclosed by the tag :" << (*tagIt).text << std::endl;
        } else { // no TagStruct with the Tag name
            std::cout << "Sorry, the tag you are looking for does not exist!" << std::endl;
        }
    }

    std::string getTagName(std::string s) {
        // return the first tag name embraced in angle brackets in passed content
        std::string tagName;
        std::string dataline = s;
        // get the position of the first "<" in the content
        int tagNameStart = dataline.find("<");
        int s_nextNameStart = tagNameStart;
        while (dataline[tagNameStart+1] == ' ') { // if a whitespace follows "<", then not a tag start
            // break the content and read the next "<"
            dataline = dataline.substr(tagNameStart+1);
            tagNameStart = dataline.find("<");
            s_nextNameStart += (tagNameStart+1);
        }
        // get the position of the first ">" in the content
        dataline = s;
        int tagNameEnd = dataline.find(">");
        int s_nextNameEnd = tagNameEnd;
        while (dataline[tagNameEnd-1] == ' ') { // if a whitespace precedes ">", then not a tag end
            // break the dataline and read the next ">"
            dataline = dataline.substr(tagNameEnd+1);
            tagNameEnd = dataline.find(">");
            s_nextNameEnd += (tagNameEnd+1);
        }
        // s_nextNameStart and s_nextNameEnd keep track of tag start and tag close in passed string content
        tagName = s.substr((s_nextNameStart+1), (s_nextNameEnd-s_nextNameStart-1));
        return tagName;
    }

    std::string getContentAfterTag(std::string c) {
        // return the truncated content after a tag by
        // finding the first tag in the passed content, and substr the content after the closing angle bracket
        std::string newContent;
        std::string dataline = c;
        // get the position of the first ">" in the content
        int newContentStart = dataline.find(">");
        while (dataline[newContentStart-1] == ' ') { // if a whitespace precedes ">", then not a tag end
            // break the dataline and find the next ">"
            dataline = dataline.substr(newContentStart+1);
            newContentStart = dataline.find(">");
        } 
        // newContentStart keeps track of the closing angle bracket in passed string content
        newContent = dataline.substr(newContentStart+1);
        return newContent;
    }

    std::string getTextAfterTag(std::string s) {
        // return the text before a tag ("after" the tag taht has been removed from content and stored in nameStack)
        // find the first tag in the passed content, and substr the content before the opening angle bracket
        std::string tagText;
        std::string dataline = s;
        // get the position of the first ">" in the content
        int nextTagStart = dataline.find("<");
        // s_nextTagStart keeps track of the opening angle bracket in passed string content
        int s_nextTagStart = nextTagStart;
        while (dataline[nextTagStart+1] == ' ') { // if a whitespace follows "<", then not a tag start
            // break the dataline and find the next "<"
            dataline = dataline.substr(nextTagStart+1);
            nextTagStart = dataline.find("<");
            s_nextTagStart += (nextTagStart+1);
        } 
        tagText = s.substr(0, s_nextTagStart);
        return tagText;
    }

    void addTag(std::string tn, std::string tt) {
        // push_back a TagStruct to TagVector if tag name not existing; else increment quantity and join text
        std::string tagName = tn;
        std::string tagText = tt;
        auto tagIt = std::find_if(TagVector.begin(), TagVector.end(), [&tagName](TagStruct& ts) { return ts.name == tagName; } );
        if (tagIt != TagVector.end()) { // found a TagStruct with the Tag name
            // increment the number of occurences by 1 and join the text
            (*tagIt).quantity += 1;
            (*tagIt).text += ":";
            (*tagIt).text += tagText;
        } else { // no TagStruct with the Tag name; add the Tag
                TagVector.push_back({tagName, 1, tagText});
        }
    }
}
