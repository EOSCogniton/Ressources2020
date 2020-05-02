\LoadClass[a4paper,12pt]{article} % Classe du document

%--------------------- Packages ------------------------

\RequirePackage[english]{babel} %Langue du document
\RequirePackage[utf8]{inputenc} %Caractères spéciaux
\RequirePackage{textcomp} %°€
\RequirePackage[section]{placeins}%Pour placement de section
\RequirePackage[T1]{fontenc} %Quelques lettres qui sont pas inclus dans UTF-8
\RequirePackage{mathtools} %Paquet pour des équations et symboles mathématiques
%\RequirePackage{siunitx} %Pour écrire avec la notation scientifique (Ex.: \num{2e+9})
\RequirePackage{float} %Pour placement d'images
\RequirePackage{graphicx} %Paquet pour insérer des images
\RequirePackage[justification=centering, width=.8\linewidth, font=small, labelfont=sc]{caption} %Pour les légendes centralisées
%\RequirePackage{subcaption}
\RequirePackage{wallpaper} % subfigure
%\RequirePackage{nomencl} 
%\makenomenclature
\RequirePackage{fancyhdr}
%\pagestyle{fancy}
%\fancyheadoffset{1cm}
%\setlength{\headheight}{2cm}
\RequirePackage{url}
\RequirePackage[hidelinks]{hyperref}%Paquet pour insérer légendes dans des sous-figures comme Figure 1a, 1b
\RequirePackage[textwidth=17cm, textheight=24cm]{geometry} %Configuration de la page




%-------------------- Informations sur le rapport ----------------------

\newcommand{\UE}[1]{\renewcommand{\UE}{#1}}
\newcommand{\sujet}[1]{\renewcommand{\sujet}{#1}}
\newcommand{\titre}[1]{\renewcommand{\titre}{#1}}
\newcommand{\enseignant}[1]{\renewcommand{\enseignant}{#1}}
\newcommand{\eleves}[1]{\renewcommand{\eleves}{#1}}

\newcommand{\fairemarges}{
%\makenomenclature
% ----- page headers
\pagestyle{fancy}
\fancyheadoffset{1cm} % horizontale
\setlength{\headheight}{1cm}
\lhead{\includegraphics[height=1cm]{logos/EPSA_Logo.png}} %Affichage de l'image au top de la page
\rhead{\nouppercase{\leftmark}}
\rfoot{\thepage}
\cfoot{}%{Rapport - \textbf{\titre}}
\lfoot{\textsc{Team Invictus 2020}}
}

% ---- title page
\newcommand{\fairepagedegarde}{
\begin{titlepage}

\ThisLRCornerWallPaper{0.6}{logos/SteinECL.jpg}
	\centering %Centraliser le contenu
	\includegraphics[width=0.6\textwidth]{logos/EPSA_Logo.png}\par\vspace{0.5cm} %Insertion du logo
	%{\scshape\LARGE École Centrale Lyon \par} %Nom de l'université
	\vspace{0.5cm}%Espace de 1,5cm
	{\scshape\Large \UE \\ \sujet \\  \par} %sous-titre
	\vspace{0.5cm}%Espace de 1cm
    \rule{\linewidth}{0.2 mm} \\[0.2 cm]
	{\huge\bfseries \titre \par} 
    \rule{\linewidth}{0.2 mm} \\[0.5 cm]
	\vspace{0.5cm}%Espace de 3cm
	\vfill
	{\large \today\par} %Affichage de la date

\end{titlepage}
}

\newcommand{\tabledematieres}{
% lire la doc fancaise du package minitoc
\setcounter{secnumdepth}{0}
\setcounter{tocdepth}{0}
%\setcounter{parttocdepth}{1} 
%\setcounter{secttocdepth}{3} 
%\doparttoc[e]
%\dosecttoc[e]
\tableofcontents
\newpage
}

%------ Custom command : preparation
% path for images in different folders
\newcommand{\imgPath}{vide}

\newcommand{\codelink}[2]{
% create link on part number, underscore is a problem
% 1. label with "_"
% 2. label display with "\_"
    \hyperref[#1]{\texttt{#2}}
}


%------ Custom commands : SUMMARY
\newcommand{\sumsys}[3]{
% system in summary, link needed
% 1. id 
% 2. system name
	\paragraph{\codelink{#1}{#2} - #3}
}

\newenvironment{sumov}{
%  summary overview env (table)
\begin{table}[H]
    \centering
    \begin{tabular}{|cllcc|}
    \hline
}{
    \\\hline
    \end{tabular}
\end{table}
}

\newcommand{\sumass}[3]{
% assembly item in summery (table header)
% 1. id
% 2. assembly name
 \codelink{#1}{#2}& \multicolumn{4}{|l|}{\bfseries #3} \\\hline
}

\newcommand{\sumpar}[6]{
% part item in summary (table row)
% 1. part id
% 2. part name
% 3. part description
% 4. make/buy 
% 5. qty
\codelink{#1}{#2} & #3 & #4 & #5 & #6\\\hline
}

%------ Custom commands : SYSTEM
\newcommand{\sys}[3]{
% description
% 1. Id
% 2. name
    \part{\codelink{#1}{#2} - #3}
}


\newenvironment{sysov}{
% system overview env (table)
\begin{table}[H]
    \centering
        \begin{tabular}{cl}
}{
    \end{tabular}
\end{table}
}

\newcommand{\sysovit}[3]{
% assembly item in system overview (table row)
% 1. assembly id
% 2. assembly name
 \codelink{#1}{#2} & #3 \\
}

\newcommand{\sysim}[1]{
% dsystem overview coured image
% 1. img path
\begin{figure}[H]
    \centering
    \includegraphics[width=\linewidth,height=.5\textheight,keepaspectratio]{\imgPath/#1}
\end{figure}
}

%------ Custom commands : ASSEMBLY
\newcommand{\ass}[3]{
% assembly page header, no link, label
% 1. id
% 2. name
    \newpage
    \section{\texttt{#2} \textbf{#3}} \label{#1}
}

\newenvironment{assov}{
% assembly overview table with parts
\begin{table}[H]
    \centering
    \begin{tabular}{|c|l|l|c|c|}
    \hline
	id & part & description & m/b & qty \\\hline
}{
    \\\hline
    \end{tabular}
\end{table}
}

\newcommand{\assovit}[6]{
% part items in the assembly overview table
% 1. part id
% 2. part name
% 3. part description
% 4. make/buy 
% 5. qty
\codelink{#1}{#2} & #3 & #4 & #5 & #6\\\hline
}

\newcommand{\assim}[1]{
% assembly exploded view (just below \assov )
% 1. img path
\begin{figure}[H]
    \centering
    \includegraphics[width=\linewidth,height=.5\textheight,keepaspectratio]{\imgPath/#1}
\end{figure}
}

%------ Custom commands : PART
\newcommand{\com}[6]{
% part header page, no link, label
% 1. part id
% 2. part name
% 3. part description
% 4. make/buy 
% 5. qty
    \newpage
    \subsection{\texttt{#2 #5} #3 (#4) }\label{#1}
}

\newcommand{\comim}[1]{
% escamotage pour optimiser la taille de la figure
% 1. img path
	\begin{figure}[H]
	\centering
	\includegraphics[width=\linewidth,height=.5\textheight,keepaspectratio]{\imgPath/#1}
	\end{figure}
}
