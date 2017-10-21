<template>

  <v-app id="inspire" dark>
    <v-navigation-drawer
      clipped
      persistent
      v-model="drawer"
      enable-resize-watcher
      app
    >
      <v-list dense>
        <v-list-tile @click="">
          <v-list-tile-action>
            <v-icon>dashboard</v-icon>
          </v-list-tile-action>
          <v-list-tile-content>
            <v-list-tile-title>Dashboard</v-list-tile-title>
          </v-list-tile-content>
        </v-list-tile>
        <v-list-tile @click="">
          <v-list-tile-action>
            <v-icon>settings</v-icon>
          </v-list-tile-action>
          <v-list-tile-content>
            <v-list-tile-title>Settings</v-list-tile-title>
          </v-list-tile-content>
        </v-list-tile>
      </v-list>
    </v-navigation-drawer>
    <v-toolbar app fixed clipped-left>
      <v-toolbar-side-icon @click.stop="drawer = !drawer"></v-toolbar-side-icon>
      <v-toolbar-title>Application</v-toolbar-title>
    </v-toolbar>
    <main>
      <v-content>
        <v-container fluid fill-height>
          <v-layout>
            <router-view></router-view>
          </v-layout>
        </v-container>
      </v-content>
    </main>
    <v-footer app fixed>
      <span><i class="fa fa-heart"/> K2000</span>
    </v-footer>
  </v-app>
</template>

<script>
export default {
  name: 'app',
  data: () => ({
    drawer: true
  })
}
</script>

<style>
 @font-face {
     font-family: 'Montserrat';
     src: url('/static/fonts/Montserrat-Regular.otf');
     font-weight: normal;
 }

 @font-face {
     font-family: 'Montserrat';
     src: url('/static/fonts/Montserrat-Bold.otf');
     font-weight: bold;
 }

 #view {
     font-family: 'Montserrat', Helvetica, Arial, sans-serif;
     position: absolute;
     top: 50px;
     bottom: 0px;
     width: 100%;
     overflow: auto;
 }

</style>
