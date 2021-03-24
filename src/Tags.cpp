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
        // firstly removes all elements from the vector before reading from new file
        TagVector.clear(); 

        // open file
        std::ifstream inputFile(fn);
        if (!inputFile){
            std::cerr << "Invalid file name!" << std::endl;
        }

        std::string line;
        std::string content;
        while (std::getline(inputFile, line)) {
            // read all lines into string content
            content = content + line;
        }        

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

        // close file
        inputFile.close();
    }

    void printTags() {
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
        }
    }

    void listTag(std::string tn) {
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
        std::string tagName;
        int start = s.find("<") + 1;
        int end = s.find(">");
        tagName = s.substr(start, end - start);
        return tagName;
    }

    std::string getContentAfterTag(std::string c) {
        std::string newContent;
        int start = c.find(">") + 1;
        newContent = c.substr(start);
        return newContent;
    }

    std::string getTextAfterTag(std::string s) {
        std::string tagText;
        int nextTagStart = s.find("<");
        tagText = s.substr(0, nextTagStart);
        return tagText;
    }

    void addTag(std::string tn, std::string tt) {
        std::string tagName = tn;
        std::string tagText = tt;
        auto tagIt = std::find_if(TagVector.begin(), TagVector.end(), [&tagName](TagStruct& ts) { return ts.name == tagName; } );
        if (tagIt != TagVector.end()) { // found a TagStruct with the Tag name
            (*tagIt).quantity += 1;
            (*tagIt).text += ":";
            (*tagIt).text += tagText;
        } else { // no TagStruct with the Tag name; add the Tag
                TagVector.push_back({tagName, 1, tagText});
        }
    }
}
