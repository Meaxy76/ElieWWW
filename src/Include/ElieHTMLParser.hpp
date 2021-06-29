/* 
 ElieWWW for Cpcdos OSx Beta 1.5
 Prototype of a HTML Parser 
  _____ _ _    __        ____        ____        __
 | ____| (_) __\ \      / /\ \      / /\ \      / /
 |  _| | | |/ _ \ \ /\ / /  \ \ /\ / /  \ \ /\ / / 
 | |___| | |  __/\ V  V /    \ V  V /    \ V  V /  
 |_____|_|_|\___| \_/\_/      \_/\_/      \_/\_/   
 */

/* We include here headers and libs for ElieWWW */

#include <iostream>
#include <map>

std::map<std::string,std::string> html_tags = {
    {"<!DOCTYPE", ""},
    {"<!doctype", ""},
    {"<html", "</html>"},
    {"<head", "</head>"},
    {"<title", "</title>"},
    {"<meta", "</meta>"},
    {"<body", "</body>"},
    {"<h1", "</h1>"},
    {"<h2", "</h2>"},
    {"<center", "</center>"},
    {"<a", "</a>"},
    {"<p", "</p>"},
    {"<ol", "</ol>"},
    {"<ul", "</ul>"},
    {"<li", "</li>"},
    {"<table", "</table>"},
    {"<td", "</td>"},
    {"<tr", "</tr>"},
    {"<img", "</img>"},
    {"<svg", "</svg>"},
    {"<div", "</div>"},
    {"<form", "</form>"},
    {"<input", ""},
    {"<nav", "</nav>"},
    {"<header", "</header>"},
    {"<footer", "</footer>"},
    {"<span", "</span>"},
    {"<strong", "</strong>"},
    {"<em", "</em>"},
    {"<link", ""},
    {"<br", ""}
};

std::map<std::string,std::string> no_contents_map = {
    {"<script", "</script>"},
    {"<style", "</style>"},
};

std::map<std::string,std::string> conversion_map = {
    {"<title", "\33\[37m\n"},
    {"<a", "\33\[34m"},
    {"<header", ""},
    {"<footer", ""},
    {"<div", "\033\[37m\n"},
    {"<span", " "},
    {"<li", " | "},
    {"<p", "\n"},
    {"<strong", "\033\[1m"},
    {"<em", "\033\[7m"},
    {"<h1", ""},
    {"<h2", ""},
    {"<ul", ""},
    {"<li", ""},
    {"<svg", ""},
    {"<link", ""},
    {"<br", ""}
};

std::string removeTagsContent(std::string html) {
    std::map<std::string,std::string>::iterator it;
    std::string starting_tag;
    std::string ending_tag;
    std::size_t position;
    std::size_t ending_pos;

    for(it = no_contents_map.begin(); it != no_contents_map.end(); it++) {
        starting_tag = it->first;
        ending_tag = it->second;
        while((position = html.find(starting_tag)) != std::string::npos) {
            ending_pos = html.find(ending_tag, position);
            html.replace(position, (ending_pos - position) + ending_tag.size(), "");
        }
    }
    return html;
}

std::string improveFormatting(std::string html) {
    std::size_t position;
    std::string token = "  ";
    while ((position = html.find(token)) != std::string::npos) {
        html.replace(position, token.size(), " ");
    }

    token = "\n \n";
    while ((position = html.find(token)) != std::string::npos) {
        html.erase(position, token.size());
    }

    token = "\n\n ";
    while ((position = html.find(token)) != std::string::npos) {
        html.erase(position, token.size());
    }

    return html;
}

std::string HTMLReader(std::string html) {
    std::map<std::string,std::string>::iterator it;
    std::size_t position;
    std::size_t ending_pos;
    std::string ending_entity = ">";
    int shift = ending_entity.size();
    std::string starting_tag;
    std::string ending_tag;

    html = removeTagsContent(html);

    for(it = html_tags.begin(); it != html_tags.end(); it++) {
        starting_tag = it->first;
        while ((position = html.find(starting_tag)) != std::string::npos) {
            ending_pos = html.find(ending_entity, position);

            if (ending_pos != std::string::npos)
                html.replace(position, (ending_pos - position) + shift, conversion_map[starting_tag]);
            else
                html.replace(position, starting_tag.size() + ending_entity.size(), conversion_map[starting_tag]);

            ending_tag = it->second;
            position = html.find(ending_tag);

            if (position == std::string::npos)
                continue;

            html.replace(position, ending_tag.size(), "\n");
            
        }
    }

    return improveFormatting(html);
}
