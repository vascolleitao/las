<div id="top"></div>
<!--
*** Thanks for checking out the Best-README-Template. If you have a suggestion
*** that would make this better, please fork the repo and create a pull request
*** or simply open an issue with the tag "enhancement".
*** Don't forget to give the project a star!
*** Thanks again! Now go create something AMAZING! :D
-->



<!-- PROJECT SHIELDS -->
<!--
*** I'm using markdown "reference style" links for readability.
*** Reference links are enclosed in brackets [ ] instead of parentheses ( ).
*** See the bottom of this document for the declaration of the reference variables
*** for contributors-url, forks-url, etc. This is an optional, concise syntax you may use.
*** https://www.markdownguide.org/basic-syntax/#reference-style-links
-->
[![Contributors][contributors-shield]][contributors-url]
[![Forks][forks-shield]][forks-url]
[![Stargazers][stars-shield]][stars-url]
[![Issues][issues-shield]][issues-url]
[![MIT License][license-shield]][license-url]
[![LinkedIn][linkedin-shield]][linkedin-url]



<!-- PROJECT LOGO -->


<br />
<div align="center">
  <a href="https://github.com/vascolleitao/las">
    <img src="images/logo/linkedin_banner_image_2.png" alt="Logo">
  </a>

<h3 align="center">LAS - Layered Algorithmic Skeletons</h3>
<h3 align="center">LAS</h3>

  <p align="center">
    LAS is an Algorithmic Skeleton Framework with multiple layers of parallelization 
    <br />
    <a href="https://github.com/vascolleitao/las"><strong>Explore the docs »</strong></a>
    <br />
    <br />
    <a href="https://github.com/vascolleitao/las">View Demo</a>
    ·
    <a href="https://github.com/vascolleitao/las/issues">Report Bug</a>
    ·
    <a href="https://github.com/vascolleitao/las/issues">Request Feature</a>
  </p>
</div>



<!-- TABLE OF CONTENTS -->
  <summary>Table of Contents</summary>
  <ol>
    <li> <a href="#getting-started">Getting Started</a> </li>
    <li><a href="#documentation">Documentation</a></li>
    <li><a href="#examples">Examples</a></li>
    <li><a href="#contact">Contact</a></li>
  </ol>


<!-- Getting Started -->
## Getting Started
<p align="right">(<a href="#top">back to top</a>)</p>

LAS has three modes of utilization:
 - Default: only uses  the sequential layer;
 - Static: uses the layers specified by de user at compile time by passing compile definitions;
 - Dynamic: compiling all the layers and choses the and choses the best one for a specific collection and skeleton. 

<!-- Documentation -->
## Documentation

See the master's thesis document
 <a href="vascolleitao.github.io/pdfs/skl_master_thesis.pdf" target="_blank">here</a>.


<p align="right">(<a href="#top">back to top</a>)</p>

<!-- Examples -->
## Examples

### Using the map skeleton with threads

Here is a simple example initializing each element with the number of the corresponding thread.

```cpp
std::vector<int> vec(1000);
auto thread_num = [](auto& i) { i = omp_get_thread_num(); };
vec >>= las::map(thread_num);
```

<p align="right">(<a href="#top">back to top</a>)</p>

<!-- CONTACT -->
## Contact

Vasco Leitão - [@vascolleitao](https://twitter.com/vascolleitao) - vascolleitao@gmail.com

Project Link: [https://github.com/vascolleitao/las](https://github.com/vascolleitao/las)

<p align="right">(<a href="#top">back to top</a>)</p>





<!-- MARKDOWN LINKS & IMAGES -->
<!-- https://www.markdownguide.org/basic-syntax/#reference-style-links -->
[contributors-shield]: https://img.shields.io/github/contributors/vascolleitao/las.svg?style=for-the-badge
[contributors-url]: https://github.com/vascolleitao/las/graphs/contributors
[forks-shield]: https://img.shields.io/github/forks/vascolleitao/las.svg?style=for-the-badge
[forks-url]: https://github.com/vascolleitao/las/network/members
[stars-shield]: https://img.shields.io/github/stars/vascolleitao/las.svg?style=for-the-badge
[stars-url]: https://github.com/vascolleitao/las/stargazers
[issues-shield]: https://img.shields.io/github/issues/vascolleitao/las.svg?style=for-the-badge
[issues-url]: https://github.com/vascolleitao/las/issues
[license-shield]: https://img.shields.io/github/license/vascolleitao/las.svg?style=for-the-badge
[license-url]: https://github.com/vascolleitao/las/blob/master/LICENSE.txt
[linkedin-shield]: https://img.shields.io/badge/-LinkedIn-black.svg?style=for-the-badge&logo=linkedin&colorB=555
[linkedin-url]: https://linkedin.com/in/vascolleitao


